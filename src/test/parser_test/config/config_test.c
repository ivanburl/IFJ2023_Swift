//
// Created by burluiva on 11/13/2023.
//
#include "config_test.h"
#include "../../../parser/parser.h"
#include "../../../utils/logger.h"
#include "stdio.h"

int parser_config_test() {
  // Grammar to be tested

  // S -> (E)
  // S -> STRING
  // E -> S
  // E -> E, S
  int returnCode = 0;
  GrammarRule grammarRule[] = {
      grammar_rule_create(S, S_SEQUENTIAL,
                          (TokenType[]){LEFT_BRACKET, E, RIGHT_BRACKET}, 3),
      grammar_rule_create(S, S_SEQUENTIAL, (TokenType[]){STRING}, 1),
      grammar_rule_create(E, E_TERMINAL, (TokenType[]){S}, 1),
      grammar_rule_create(E, E_TERMINAL, (TokenType[]){E, COMMA, S}, 3),
  };
  Grammar grammar = grammar_create(grammarRule, 4);

  Parser parser;
  parser_init(&parser);
  parser_create(&parser, &grammar);
  parser_configure(&parser);

  LOG_INFO_WHITE("Debug automata after configuration...");

  for (int i = 0;i<MAX_AUTOMATA_STATES_NUMBER;i++) {
    bool nonNull = false;
    for (int j = 0; j < MAX_AUTOMATA_EDGE_TYPES; j++) {
      if (parser.automata.automata[i][j] == -1) continue;
      if (!nonNull) {
        printf("State: %d ; Links: ", i);
        nonNull = true;
      }
      printf("by %d -> %d, ", j, parser.automata.automata[i][j]);
    }
    if (nonNull) printf("\n");
  }
  printf("Return states: \n");
  for (int i=0;i<MAX_AUTOMATA_STATES_NUMBER;i++) {
    if (parser.automata.stateReturnValues[i] != -1)
      printf("State: %d returns %d\n", i, parser.automata.stateReturnValues[i]);
  }

  LOG_INFO("First iteration finished!");

  return returnCode;
}