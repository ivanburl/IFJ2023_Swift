//
// Created by burluiva on 11/13/2023.
//

#include "grammar_test.h"
#include "../../model/grammar/grammar.h"
#include "../../model/grammar/rule/grammar_rule.h"
#include"../../utils/logger.h"

int grammar_first_nullable_simple_test() {
  int returnCode = 0;

  // S -> ID
  // S -> E F S
  // E -> F
  // E -> INTEGER
  // F ->
  // F -> STRING

  GrammarRule grammarRule[] = {
      grammar_rule_create(S, S_SEQUENTIAL, (TokenType[]){ID}, 1),
      grammar_rule_create(S, S_SEQUENTIAL, (TokenType[]){E, F, S}, 3),
      grammar_rule_create(E, S_SEQUENTIAL, (TokenType[]){F}, 1),
      grammar_rule_create(E, S_SEQUENTIAL, (TokenType[]){INTEGER}, 1),
      grammar_rule_create(F, S_SEQUENTIAL, (TokenType[]){}, 0),
      grammar_rule_create(F, S_SEQUENTIAL, (TokenType[]){STRING}, 1)};
  Grammar grammar = grammar_create(grammarRule, 6);

  printf("Symbol S is equal to %d\n", S);
  printf("Symbol E is equal to %d\n", E);
  printf("Symbol F is equal to %d\n", F);
  printf("Symbol ID is equal to %d\n", ID);
  printf("Symbol INTEGER is equal to %d\n", INTEGER);
  printf("Symbol STRING is equal to %d\n", STRING);

  for (int i = NON_TERMINAL_UNDEFINED; i < MAX_TOKEN_TYPES_NUMBER; i++) {
    bool notFound = true;
    for (int j = 0; j < MAX_TOKEN_TYPES_NUMBER; j++) {
      if (notFound && grammar.first[i][j]) {
        printf("First for %d: ", i);
        notFound = false;
      }
      if (grammar.first[i][j])
        printf("%d, ", j);
    }
    if (!notFound)
      printf("\n");
  }

  for (int i = NON_TERMINAL_UNDEFINED; i < MAX_TOKEN_TYPES_NUMBER; i++) {
    if (grammar.nullable[i])
      printf("Symbol %d is nullable!\n", i);
  }

  return returnCode;
}

int grammar_first_nullable_simple_test_2() {
  int returnCode = 0;

  // S -> F = E
  // S -> E
  // E -> F
  // F -> ID
  // F -> COLON E

  GrammarRule grammarRule[] = {
      grammar_rule_create(S, S_SEQUENTIAL, (TokenType[]){F, EQUAL, E}, 3),
      grammar_rule_create(S, S_SEQUENTIAL, (TokenType[]){E}, 3),
      grammar_rule_create(E, S_SEQUENTIAL, (TokenType[]){F}, 1),
      grammar_rule_create(F, S_SEQUENTIAL, (TokenType[]){ID}, 1),
      grammar_rule_create(F, S_SEQUENTIAL, (TokenType[]){COLON, E}, 2)};
  Grammar grammar = grammar_create(grammarRule, 5);

  printf("Symbol S is equal to %d\n", S);
  printf("Symbol E is equal to %d\n", E);
  printf("Symbol F is equal to %d\n", F);
  printf("Symbol ID is equal to %d\n", ID);
  printf("Symbol EQUAL is equal to %d\n", EQUAL);
  printf("Symbol COLON is equal to %d\n", COLON);

  for (int i = NON_TERMINAL_UNDEFINED; i < MAX_TOKEN_TYPES_NUMBER; i++) {
    bool notFound = true;
    for (int j = 0; j < MAX_TOKEN_TYPES_NUMBER; j++) {
      if (notFound && grammar.first[i][j]) {
        printf("First for %d: ", i);
        notFound = false;
      }
      if (grammar.first[i][j])
        printf("%d, ", j);
    }
    if (!notFound)
      printf("\n");
  }

  for (int i = NON_TERMINAL_UNDEFINED; i < MAX_TOKEN_TYPES_NUMBER; i++) {
    if (grammar.nullable[i])
      printf("Symbol %d is nullable!\n", i);
  }

  return returnCode;
}

int grammar_test() {
  LOG_INFO("First grammar test started!");
  grammar_first_nullable_simple_test();
  LOG_INFO("Second grammar test started!");
  grammar_first_nullable_simple_test_2();
  return 0;
}
