//
// Created by burluiva on 10/28/2023.
//

#ifndef IFJ2023_SWIFT_GRAMMAR_H
#define IFJ2023_SWIFT_GRAMMAR_H

#include "../grammar/rule/grammar_rule.h"
#include "../../structures/vector/vector.h"

#define MAX_GRAMMAR_RULES_SIZE 128

typedef struct grammar_t {
  int rulesNumber;
  GrammarRule grammarRules[MAX_GRAMMAR_RULES_SIZE];
  IntVector first[MAX_GRAMMAR_RULES_SIZE];
  int nullable[MAX_GRAMMAR_RULES_SIZE];
} Grammar;

void grammar_init(Grammar* grammar);
Grammar grammar_create(GrammarRule* grammarRules, int numberOfRules);
void grammar_free(Grammar* grammar);

#endif // IFJ2023_SWIFT_GRAMMAR_H
