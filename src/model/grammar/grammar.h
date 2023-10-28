//
// Created by burluiva on 10/28/2023.
//

#ifndef IFJ2023_SWIFT_GRAMMAR_H
#define IFJ2023_SWIFT_GRAMMAR_H

#include "../../structures/vector/vector.h"
#include "../grammar/rule/grammar_rule.h"
#include "stdbool.h"
#define MAX_GRAMMAR_RULES_SIZE 128

typedef struct grammar_t {
  int rulesNumber;
  GrammarRule grammarRules[MAX_GRAMMAR_RULES_SIZE];
  bool first[MAX_TOKEN_TYPES_NUMBER][MAX_TOKEN_TYPES_NUMBER];
  bool nullable[MAX_TOKEN_TYPES_NUMBER];
} Grammar;

void grammar_init(Grammar *grammar);
Grammar grammar_create(GrammarRule *grammarRules, int numberOfRules);

#endif // IFJ2023_SWIFT_GRAMMAR_H
