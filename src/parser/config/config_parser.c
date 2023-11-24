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

  int llGrammarRulesCount = 56; // 52
  GrammarRule llGrammarRules[] = {
      grammar_rule_create(STS, NULL, NULL, NULL, (TokenType[]){S, STS_TMP}, 2),
      grammar_rule_create(STS_TMP, NULL, NULL, NULL,
                          (TokenType[]){DELIMITER, S, STS_TMP}, 3),
      grammar_rule_create(STS_TMP, NULL, NULL, NULL, (TokenType[]){}, 0),

      grammar_rule_create(S, NULL, NULL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(S, NULL, BlockWhileInterCode, WhileInitInterCode, (TokenType[]){WHILE, COND, BLOCK}, 3),
      grammar_rule_create(S, NULL, PostOrderForIf, PreOrderForIf,
                          (TokenType[]){IF, COND, BLOCK, IF_ELSE}, 4),
      grammar_rule_create(S, NULL, NULL, NULL, (TokenType[]){E}, 1),
      grammar_rule_create(S, NULL, NULL, NULL, (TokenType[]){D}, 1),
      grammar_rule_create(S, NULL, ReturnInterCode, NULL, (TokenType[]){RETURN, E}, 2),
      grammar_rule_create(S, NULL, ContinueInterCode, NULL, (TokenType[]){CONTINUE}, 1),
      grammar_rule_create(S, NULL, BreakInterCode, NULL, (TokenType[]){BREAK}, 1),
      grammar_rule_create(COND, NULL, CondInterCode, NULL, (TokenType[]){E}, 1),
      grammar_rule_create(COND, NULL, NULL, NULL, (TokenType[]){LET, ID}, 2),   //TODO: Create definition for this 
      grammar_rule_create(IF_ELSE, NULL, NULL, PreOrderForIfEslse, (TokenType[]){}, 0),
      grammar_rule_create(IF_ELSE, NULL, NULL, PreOrderForIfEslse, (TokenType[]){ELSE, BLOCK}, 2),
      grammar_rule_create(
          BLOCK, NULL, NULL, NULL,
          (TokenType[]){LEFT_CURL_BRACKET, STS, RIGHT_CURL_BRACKET}, 3),
      grammar_rule_create(D, NULL, VarIdInit, NULL,
                          (TokenType[]){VAR, ID, TANN_NULL, INIT}, 4),
      grammar_rule_create(D, NULL, VarIdInit, NULL,
                          (TokenType[]){LET, ID, TANN_NULL, INIT}, 4),  //TODO: Create constant support
      grammar_rule_create(D, NULL, FuncInitializeEscape, FuncInitialize,
                          (TokenType[]){FUNC, ID, LEFT_BRACKET, PARAMS,
                                        RIGHT_BRACKET, ARROW, TYPE, BLOCK},
                          8),
      grammar_rule_create(PARAM, NULL, NULL, NULL, (TokenType[]){FUNC_ID, ID, TANN},
                          3),
      grammar_rule_create(FUNC_ID, NULL, NULL, NULL, (TokenType[]){ID}, 1),
      grammar_rule_create(FUNC_ID, NULL, NULL, NULL, (TokenType[]){UNDERSCORE}, 1),
      grammar_rule_create(PARAMS, NULL, NULL, NULL, (TokenType[]){PARAM, PARAMS_TMP},
                          2),
      grammar_rule_create(PARAMS_TMP, NULL, NULL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(PARAMS_TMP, NULL, NULL, NULL,
                          (TokenType[]){COMMA, PARAM, PARAMS_TMP}, 3),
      grammar_rule_create(PARAMS, NULL, NULL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(TANN, NULL, NULL, NULL, (TokenType[]){COLON, TYPE}, 2),
      grammar_rule_create(TANN_NULL, NULL, NULL, NULL, (TokenType[]){TANN}, 1),
      grammar_rule_create(TANN_NULL, NULL, NULL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(INIT, NULL, InitProcess, NULL, (TokenType[]){ASSIGN, E}, 2),
      grammar_rule_create(INIT, NULL, NULL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(F, NULL, NULL, NULL,
                          (TokenType[]){LEFT_BRACKET, E, RIGHT_BRACKET}, 3),
      grammar_rule_create(F, NULL, FuncCall, NULL, (TokenType[]){ID, F_CALL}, 2),
      grammar_rule_create(F, NULL, StoreInt, NULL, (TokenType[]){INTEGER}, 1),
      grammar_rule_create(F, NULL, StoreString, NULL, (TokenType[]){STRING}, 1),
      grammar_rule_create(F, NULL, StoreDouble, NULL, (TokenType[]){DOUBLE}, 1),
      grammar_rule_create(F, NULL, StoreBool, NULL, (TokenType[]){BOOLEAN}, 1),
      grammar_rule_create(F, NULL, NotInterCode, NULL, (TokenType[]){HARD_UNWRAP, F}, 2),
      grammar_rule_create(F_CALL, NULL, FuncArgAdd, NULL,
                          (TokenType[]){LEFT_BRACKET, ARGS, RIGHT_BRACKET}, 3),
      grammar_rule_create(F_CALL, NULL, FuncArgAdd, NULL, (TokenType[]){}, 0),
      grammar_rule_create(F_CALL, NULL, HardUnwrapInterCode, NULL,
                          (TokenType[]){HARD_UNWRAP}, 1),
      grammar_rule_create(ARGS, NULL, NULL, NULL, (TokenType[]){ARG, ARGS_TMP}, 1),
      grammar_rule_create(ARGS_TMP, NULL, NULL, NULL, (TokenType[]){}, 0),
      grammar_rule_create(ARGS_TMP, NULL, NULL, NULL,
                          (TokenType[]){COMMA, ARG, ARGS_TMP}, 3),

      grammar_rule_create(ARG, NULL, PushArg, NULL, (TokenType[]){E, ARG_TMP}, 2),
      grammar_rule_create(ARG_TMP, NULL, NULL, NULL, (TokenType[]){COLON, E}, 2),
      grammar_rule_create(ARG_TMP, NULL, NULL, NULL, (TokenType[]){}, 0),

      grammar_rule_create(TYPE, NULL, NULL, NULL, (TokenType[]){INT_TYPE}, 1),
      grammar_rule_create(TYPE, NULL, NULL, NULL, (TokenType[]){INT_NULLABLE_TYPE},
                          1),
      grammar_rule_create(TYPE, NULL, NULL, NULL, (TokenType[]){STRING}, 1),
      grammar_rule_create(TYPE, NULL, NULL, NULL, (TokenType[]){STRING_NULLABLE_TYPE},
                          1),
      grammar_rule_create(TYPE, NULL, NULL, NULL, (TokenType[]){DOUBLE_TYPE}, 1),
      grammar_rule_create(TYPE, NULL, NULL, NULL, (TokenType[]){DOUBLE_NULLABLE_TYPE},
                          1),
      grammar_rule_create(TYPE, NULL, NULL, NULL, (TokenType[]){BOOLEAN_TYPE}, 1),
      grammar_rule_create(TYPE, NULL, NULL, NULL, (TokenType[]){BOOLEAN_NULLABLE_TYPE}, 1),

      grammar_rule_create(E, NULL, GetF, NULL, (TokenType[]){F}, 1),

      // TODO BOOLEAN
      // TODO BOOLEAN NULLABLE
  };

  grammar_configure(parser->llParser->llGrammar, llGrammarRules,
                    llGrammarRulesCount);

  ll_parser_configure(parser->llParser);
  // TODO add boolean operations
  int pGrammarRulesCount = 14;
  GrammarRule pGrammarRules[] = {
      grammar_rule_create(E, NULL, SumInterCode, NULL, (TokenType[]){E, PLUS, E}, 3),
      grammar_rule_create(E, NULL, SubInterCode, NULL, (TokenType[]){E, MINUS, E}, 3),
      grammar_rule_create(E, NULL, MulInterCode, NULL, (TokenType[]){E, MULTIPLY, E}, 3),
      grammar_rule_create(E, NULL, DivInterCode, NULL, (TokenType[]){E, DIVIDE, E}, 3),
      grammar_rule_create(E, NULL, EqualInterCode, NULL, (TokenType[]){E, EQUAL, E}, 3),
      grammar_rule_create(E, NULL, NotEqualInterCode, NULL, (TokenType[]){E, NOT_EQUAL, E}, 3),
      grammar_rule_create(E, NULL, GreaterInterCode, NULL, (TokenType[]){E, GREATER, E}, 3),
      grammar_rule_create(E, NULL, LessInterCode, NULL, (TokenType[]){E, LESS, E}, 3),
      grammar_rule_create(E, NULL, GreaterEqualInterCode, NULL, (TokenType[]){E, GREATER_EQUAL, E}, 3),
      grammar_rule_create(E, NULL, LessEqualInterCode, NULL, (TokenType[]){E, LESS_EQUAL, E}, 3),
      grammar_rule_create(E, NULL, SoftUnwrapInterCode, NULL, (TokenType[]){E, SOFT_UNWRAP, E}, 3),
      grammar_rule_create(E, NULL, OrInterCode, NULL, (TokenType[]){E, LOGICAL_OR, E}, 3),
      grammar_rule_create(E, NULL, AndInterCode, NULL, (TokenType[]){E, LOGICAL_AND, E}, 3),
      grammar_rule_create(E, NULL, GetF, NULL, (TokenType[]){F}, 1),
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
