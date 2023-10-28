//
// Created by burluiva on 10/28/2023.
//

#include "grammar.h"

void calculate_nullable(Grammar* grammarRule);
void calculate_first(Grammar* grammarRule);

void grammar_init(Grammar* grammar) {
  assert(grammar);
  grammar->rulesNumber = 0;
  for (int i=0;i<MAX_GRAMMAR_RULES_SIZE;i++) {
    grammar_rule_init(&grammar->grammarRules[i]);
    grammar->nullable[i] = 0;
    IntVector_init(&grammar->first[i]);
  }
}

Grammar grammar_create(GrammarRule* grammarRules, int numberOfRules) {
  assert(grammarRules);
  assert(numberOfRules > 0 && numberOfRules < MAX_GRAMMAR_RULES_SIZE);
  Grammar grammar;
  grammar_init(&grammar);
  grammar.rulesNumber = numberOfRules;
  for (int i=0;i<numberOfRules;i++) {
    grammar.grammarRules[i] = grammarRules[i];
  }
  calculate_nullable(&grammar);
  calculate_first(&grammar);
}

void grammar_free(Grammar* grammar) {
  assert(grammar);
  grammar->rulesNumber = 0;
  for (int i=0;i<MAX_GRAMMAR_RULES_SIZE;i++) {
    grammar->nullable[i] = 0;
    IntVector_free(&grammar->first[i]);
  }
}

void calculate_nullable(Grammar* grammarRule) {

}

void calculate_first(Grammar* grammarRule) {

}