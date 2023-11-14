//
// Created by burluiva on 10/28/2023.
//

#include "grammar.h"

void calculate_nullable(Grammar *grammar);
void calculate_first(Grammar *grammar);

void grammar_init(Grammar *grammar) {
  assert(grammar);
  grammar->rulesNumber = 0;
  for (int i = 0; i < MAX_GRAMMAR_RULES_SIZE; i++) {
    grammar_rule_init(&grammar->grammarRules[i]);
  }

  for (int i = 0; i < MAX_TOKEN_TYPES_NUMBER; i++) {
    for (int j = 0; j < MAX_TOKEN_TYPES_NUMBER; j++) {
      grammar->first[i][j] = 0;
    }
    grammar->nullable[i] = false;
  }
}

Grammar grammar_create(GrammarRule *grammarRules, int numberOfRules) {
  assert(grammarRules);
  assert(numberOfRules >= 0 && numberOfRules <= MAX_GRAMMAR_RULES_SIZE);
  Grammar grammar;
  grammar_init(&grammar);
  grammar.rulesNumber = numberOfRules;
  for (int i = 0; i < numberOfRules; i++) {
    grammar.grammarRules[i] = grammarRules[i];
  }
  calculate_nullable(&grammar);
  calculate_first(&grammar);
  return grammar;
}

void calculate_nullable(Grammar *grammar) {
  assert(grammar);
  bool changed = true;
  while (changed) {
    changed = false;
    for (int i = 0; i < grammar->rulesNumber; i++) {
      int tokenType = grammar->grammarRules[i].resultTokenType;
      if (grammar->nullable[tokenType] == 1)
        continue;

      int tmp = 1;
      for (int j = 0; j < grammar->grammarRules[i].productionsNumber; j++) {
        tmp &= grammar->nullable[grammar->grammarRules[i].productions[j]];
      }
      grammar->nullable[tokenType] = tmp;

      if (grammar->nullable[tokenType] == 1)
        changed = true;
    }
  }
}

void calculate_first(Grammar *grammar) {
  assert(grammar);
  bool changed = true;
  for (int i=UNDEFINED;i<NON_TERMINAL_UNDEFINED; i++) {
    grammar->first[i][i] = true;
  }
  while (changed) {
    changed = false;
    for (int i = 0; i < grammar->rulesNumber; i++) {
      int sourceTokenType = grammar->grammarRules[i].resultTokenType;
      for (int j = 0; j < grammar->grammarRules[i].productionsNumber; j++) {
        int destTokenType = grammar->grammarRules[i].productions[j];
        if (j != 0 &&
            !grammar->nullable[grammar->grammarRules[i].productions[j - 1]])
          break;
        for (int k = 0; k < MAX_TOKEN_TYPES_NUMBER; k++) {
          changed |= grammar->first[sourceTokenType][k] == false &&
                     grammar->first[destTokenType][k] == true;
          grammar->first[sourceTokenType][k] |=
              grammar->first[destTokenType][k];
        }
      }
    }
  }
}