//
// Created by burluiva on 10/28/2023.
//

#include "config_parser.h"
#include "../../codegen/inter_code/inter_code.h"
#include "../../structures/hashmap/hashmap.h"

Error ifj_2023_parser_config(Parser *parser) {
  assert(parser);
  // TODO memory free control
  parser->llParser = malloc(sizeof(LLParser));
  if (parser->llParser == NULL) {
    return error_create(FATAL, "Out of memory!");
  }
  ll_parser_init(parser->llParser);
  parser->expressionParser = malloc(sizeof(PParser));
  if (parser->expressionParser == NULL) {
    return error_create(FATAL, "Out of memory!");
  }
  precedence_parser_init(parser->expressionParser);
  parser->llParser->llGrammar = malloc(sizeof(Grammar));
  if (parser->llParser->llGrammar == NULL) {
    return error_create(FATAL, "Out of memory!");
  }
  grammar_init(parser->llParser->llGrammar);
  parser->expressionParser->pGrammar = malloc(sizeof(Grammar));
  if (parser->expressionParser->pGrammar == NULL) {
    return error_create(FATAL, "Out of memory!");
  }
  grammar_init(parser->expressionParser->pGrammar);

  assert(parser->expressionParser && parser->llParser &&
         "Set the ll parser and precedence parser");

  int llGrammarRulesCount = 50;
  GrammarRule llGrammarRules[] = {
      grammar_rule_create(STS, NULL, (TokenType[]){S, STS_TMP}, 2),
      grammar_rule_create(STS, NULL, (TokenType[]){}, 0),
      grammar_rule_create(STS_TMP, NULL, (TokenType[]){DELIMITER, S, STS_TMP},
                          3),
      grammar_rule_create(STS_TMP, NULL, (TokenType[]){}, 0),
      grammar_rule_create(S, NULL, (TokenType[]){WHILE, COND, BLOCK}, 3),
      grammar_rule_create(S, NULL, (TokenType[]){IF, COND, BLOCK, IF_ELSE}, 4),
      grammar_rule_create(S, NULL, (TokenType[]){E}, 1),
      grammar_rule_create(S, NULL, (TokenType[]){D}, 1),
      grammar_rule_create(S, NULL, (TokenType[]){RETURN, E}, 2),
      //TODO S -> continue
      //TODO s -> break
      grammar_rule_create(COND, NULL, (TokenType[]){E}, 1),
      grammar_rule_create(COND, NULL, (TokenType[]){LET, ID}, 2),
      grammar_rule_create(IF_ELSE, NULL, (TokenType[]){}, 0),
      grammar_rule_create(IF_ELSE, NULL, (TokenType[]){ELSE, BLOCK}, 2),
      grammar_rule_create(
          BLOCK, NULL,
          (TokenType[]){LEFT_CURL_BRACKET, STS, RIGHT_CURL_BRACKET}, 3),
      grammar_rule_create(D, NULL, (TokenType[]){VAR, ID, TANN_NULL, INIT}, 4),
      grammar_rule_create(D, NULL, (TokenType[]){LET, ID, TANN_NULL, INIT}, 4),
      grammar_rule_create(D, NULL,
                          (TokenType[]){FUNC, ID, LEFT_BRACKET, PARAMS,
                                        RIGHT_BRACKET, ARROW, TYPE, BLOCK},
                          7),
      grammar_rule_create(PARAM, NULL, (TokenType[]){FUNC_ID, ID, TANN}, 3),
      grammar_rule_create(FUNC_ID, NULL, (TokenType[]){ID}, 1),
      grammar_rule_create(FUNC_ID, NULL, (TokenType[]){UNDERSCORE}, 1),
      grammar_rule_create(PARAMS, NULL, (TokenType[]){PARAM, PARAMS_TMP}, 2),
      grammar_rule_create(PARAMS_TMP, NULL, (TokenType[]){}, 0),
      grammar_rule_create(PARAMS_TMP, NULL,
                          (TokenType[]){COMMA, PARAM, PARAMS_TMP}, 3),
      grammar_rule_create(PARAMS, NULL, (TokenType[]){}, 0),
      grammar_rule_create(TANN, NULL, (TokenType[]){COLON, TYPE}, 2),
      grammar_rule_create(TANN_NULL, NULL, (TokenType[]){TANN}, 1),
      grammar_rule_create(TANN_NULL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(INIT, NULL, (TokenType[]){EQUAL, E}, 2),
      grammar_rule_create(INIT, NULL, (TokenType[]){}, 0),
      grammar_rule_create(
          F, NULL, (TokenType[]){LEFT_BRACKET, UNDERSCORE, RIGHT_BRACKET}, 3),
      grammar_rule_create(F, NULL, (TokenType[]){ID, F_CALL}, 2),
      grammar_rule_create(F, NULL, (TokenType[]){INTEGER}, 1),
      grammar_rule_create(F, NULL, (TokenType[]){STRING}, 1),
      grammar_rule_create(F, NULL, (TokenType[]){DOUBLE}, 1),
      grammar_rule_create(F, NULL, (TokenType[]){BOOLEAN}, 1),
      //Theoretically it should be here
      grammar_rule_create(F, NULL, (TokenType[]){ID}, 1),
      grammar_rule_create(FUNC_ID, NULL, (TokenType[]){HARD_UNWRAP, F}, 2),
      grammar_rule_create(F_CALL, NULL,
                          (TokenType[]){LEFT_BRACKET, ARGS, RIGHT_BRACKET}, 3),
      grammar_rule_create(F_CALL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(F_CALL, HardUnwrapInterCode, (TokenType[]){HARD_UNWRAP}, 1),
      grammar_rule_create(ARGS, NULL, (TokenType[]){ARG, ARGS_TMP}, 1),
      grammar_rule_create(ARGS_TMP, NULL, (TokenType[]){}, 0),
      grammar_rule_create(ARGS_TMP, NULL, (TokenType[]){COMMA, ARG, ARGS_TMP},
                          3),
      grammar_rule_create(ARG, NULL, (TokenType[]){ID, COLON, E}, 3),
      grammar_rule_create(ARG, NULL, (TokenType[]){E}, 1),

      grammar_rule_create(TYPE, NULL, (TokenType[]){INT_TYPE}, 1),
      grammar_rule_create(TYPE, NULL, (TokenType[]){INT_NULLABLE_TYPE}, 1),
      grammar_rule_create(TYPE, NULL, (TokenType[]){STRING}, 1),
      grammar_rule_create(TYPE, NULL, (TokenType[]){STRING_NULLABLE_TYPE}, 1),
      grammar_rule_create(TYPE, NULL, (TokenType[]){DOUBLE_TYPE}, 1),
      grammar_rule_create(TYPE, NULL, (TokenType[]){DOUBLE_NULLABLE_TYPE}, 1),
      //TODO BOOLEAN
      //TODO BOOLEAN NULLABLE

  };

  grammar_configure(parser->llParser->llGrammar, llGrammarRules,
                    llGrammarRulesCount);

  ll_parser_configure(parser->llParser);
  //TODO add boolean operations
  int pGrammarRulesCount = 12;
  GrammarRule pGrammarRules[] = {
      grammar_rule_create(E, SumInterCode, (TokenType[]){E, PLUS, E}, 3),
      grammar_rule_create(E, SubInterCode, (TokenType[]){E, MINUS, E}, 3),
      grammar_rule_create(E, MulInterCode, (TokenType[]){E, MULTIPLY, E}, 3),
      grammar_rule_create(E, DivInterCode, (TokenType[]){E, DIVIDE, E}, 3),
      grammar_rule_create(E, EqualInterCode, (TokenType[]){E, EQUAL, E}, 3),
      grammar_rule_create(E, NotEqualInterCode, (TokenType[]){E, NOT_EQUAL, E}, 3),
      grammar_rule_create(E, GreaterInterCode, (TokenType[]){E, GREATER, E}, 3),
      grammar_rule_create(E, LessInterCode, (TokenType[]){E, LESS, E}, 3),
      grammar_rule_create(E, GreaterEqualInterCode, (TokenType[]){E, GREATER_EQUAL, E}, 3),
      grammar_rule_create(E, LessEqualInterCode, (TokenType[]){E, LESS_EQUAL, E}, 3),
      grammar_rule_create(E, SoftUnwrapInterCode, (TokenType[]){E, SOFT_UNWRAP, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){F}, 1)
  };

  grammar_configure(parser->expressionParser->pGrammar, pGrammarRules,
                    pGrammarRulesCount);
  int operatorPriority[MAX_TOKEN_TYPES_NUMBER] = {
      [MULTIPLY] = 1,      [DIVIDE] = 1,     [MINUS] = 2,      [PLUS] = 2,
      [EQUAL] = 3,         [NOT_EQUAL] = 3,  [GREATER] = 3,    [LESS] = 3,
      [GREATER_EQUAL] = 3, [LESS_EQUAL] = 3, [SOFT_UNWRAP] = 4};
  int operatorAssociation[MAX_TOKEN_TYPES_NUMBER] = {
      [MULTIPLY] = -1,     [DIVIDE] = -1,    [MINUS] = -1,     [PLUS] = -1,
      [EQUAL] = 0,         [NOT_EQUAL] = 0,  [GREATER] = 0,    [LESS] = 0,
      [GREATER_EQUAL] = 0, [LESS_EQUAL] = 0, [SOFT_UNWRAP] = 1};
  precedence_parser_configure(parser->expressionParser, parser->expressionParser->pGrammar,
                              operatorPriority,
                              operatorAssociation);
}
