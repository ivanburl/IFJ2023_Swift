//
// Created by burluiva on 10/28/2023.
//

#include "config_parser.h"
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

  int llGrammarRulesCount = 52;//52
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
      grammar_rule_create(S, NULL, (TokenType[]){CONTINUE}, 1),
      grammar_rule_create(S, NULL, (TokenType[]){BREAK}, 1),
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
      grammar_rule_create(INIT, NULL, (TokenType[]){ASSIGN, E}, 2),
      grammar_rule_create(INIT, NULL, (TokenType[]){}, 0),
      grammar_rule_create(
          F, NULL, (TokenType[]){LEFT_BRACKET, E, RIGHT_BRACKET}, 3),
      grammar_rule_create(F, NULL, (TokenType[]){ID, F_CALL}, 2),
      grammar_rule_create(F, NULL, (TokenType[]){INTEGER}, 1),
      grammar_rule_create(F, NULL, (TokenType[]){STRING}, 1),
      grammar_rule_create(F, NULL, (TokenType[]){DOUBLE}, 1),
      grammar_rule_create(F, NULL, (TokenType[]){BOOLEAN}, 1),
      grammar_rule_create(F, NULL, (TokenType[]){HARD_UNWRAP, F}, 2),
      grammar_rule_create(F_CALL, NULL,
                          (TokenType[]){LEFT_BRACKET, ARGS, RIGHT_BRACKET}, 3),
      grammar_rule_create(F_CALL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(F_CALL, NULL, (TokenType[]){HARD_UNWRAP}, 1),
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
      // TODO BOOLEAN
      // TODO BOOLEAN NULLABLE

      /// THESE RULES ARE NOT THE PART OF PARSER TREE, ONLY FOR NEXT AND FORWARD
      /// CALC
//      grammar_rule_create(E1_TMP, NULL, (TokenType[]){}, 0),
//      grammar_rule_create(E2_TMP, NULL, (TokenType[]){}, 0),
//      grammar_rule_create(E3_TMP, NULL, (TokenType[]){}, 0),
//      grammar_rule_create(E4_TMP, NULL, (TokenType[]){}, 0),
//      grammar_rule_create(E5_TMP, NULL, (TokenType[]){}, 0),
//
//      grammar_rule_create(E, NULL, (TokenType[]){E1, E1_TMP}, 2),
//      grammar_rule_create(E1_TMP, NULL, (TokenType[]){LOGICAL_OR, E1, E1_TMP},
//                          3),
//      grammar_rule_create(E1_TMP, NULL, (TokenType[]){LOGICAL_AND, E1, E1_TMP},
//                          3),
//
//      grammar_rule_create(E1, NULL, (TokenType[]){E2, E2_TMP}, 2),//TODO think about right association
//      grammar_rule_create(E2_TMP, NULL, (TokenType[]){SOFT_UNWRAP, E2, E2_TMP},
//                          3),
//
//      grammar_rule_create(E2, NULL, (TokenType[]){E3, E3_TMP}, 2),
//      grammar_rule_create(E3_TMP, NULL, (TokenType[]){EQUAL, E3, E3_TMP}, 3),
//      grammar_rule_create(E3_TMP, NULL, (TokenType[]){GREATER, E3, E3_TMP}, 3),
//      grammar_rule_create(E3_TMP, NULL, (TokenType[]){LESS, E3, E3_TMP}, 3),
//      grammar_rule_create(E3_TMP, NULL,
//                          (TokenType[]){GREATER_EQUAL, E3, E3_TMP}, 3),
//      grammar_rule_create(E3_TMP, NULL, (TokenType[]){LESS_EQUAL, E3, E3_TMP},
//                          3),
//      grammar_rule_create(E3_TMP, NULL, (TokenType[]){NOT_EQUAL, E3, E3_TMP},
//                          3),
//
//      grammar_rule_create(E3, NULL, (TokenType[]){E4, E4_TMP}, 2),
//      grammar_rule_create(E4_TMP, NULL, (TokenType[]){PLUS, E4, E4_TMP}, 3),
//      grammar_rule_create(E4_TMP, NULL, (TokenType[]){MINUS, E4, E4_TMP}, 3),
//
//      grammar_rule_create(E4, NULL, (TokenType[]){E5, E5_TMP}, 2),
//      grammar_rule_create(E5_TMP, NULL, (TokenType[]){MULTIPLY, E5, E5_TMP}, 3),
//      grammar_rule_create(E4_TMP, NULL, (TokenType[]){DIVIDE, E5, E5_TMP}, 3),
//
//      grammar_rule_create(E5, NULL, (TokenType[]){F}, 1),
  };

  grammar_configure(parser->llParser->llGrammar, llGrammarRules,
                    llGrammarRulesCount);

  ll_parser_configure(parser->llParser);
  // TODO add boolean operations
  int pGrammarRulesCount = 14;
  GrammarRule pGrammarRules[] = {
      grammar_rule_create(E, NULL, (TokenType[]){E, PLUS, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, MINUS, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, MULTIPLY, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, DIVIDE, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, EQUAL, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, NOT_EQUAL, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, GREATER, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, LESS, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, GREATER_EQUAL, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, LESS_EQUAL, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, SOFT_UNWRAP, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, LOGICAL_OR, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){E, LOGICAL_AND, E}, 3),
      grammar_rule_create(E, NULL, (TokenType[]){F}, 1),
  };

  grammar_configure(parser->expressionParser->pGrammar, pGrammarRules,
                    pGrammarRulesCount);
  int operatorPriority[MAX_TOKEN_TYPES_NUMBER] = {
      [MULTIPLY] = 1,   [DIVIDE] = 1,      [MINUS] = 2,
      [PLUS] = 2,       [EQUAL] = 3,       [NOT_EQUAL] = 3,
      [GREATER] = 3,    [LESS] = 3,        [GREATER_EQUAL] = 3,
      [LESS_EQUAL] = 3, [SOFT_UNWRAP] = 4, [LOGICAL_OR] = 5,
      [LOGICAL_AND] = 5};
  int operatorAssociation[MAX_TOKEN_TYPES_NUMBER] = {
      [MULTIPLY] = -1,   [DIVIDE] = -1,     [MINUS] = -1,
      [PLUS] = -1,       [EQUAL] = 0,       [NOT_EQUAL] = 0,
      [GREATER] = 0,     [LESS] = 0,        [GREATER_EQUAL] = 0,
      [LESS_EQUAL] = 0,  [SOFT_UNWRAP] = 1, [LOGICAL_OR] = -1,
      [LOGICAL_AND] = -1};
  precedence_parser_configure(parser->expressionParser,
                              parser->expressionParser->pGrammar,
                              operatorPriority, operatorAssociation);
}
