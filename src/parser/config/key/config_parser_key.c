//
// Created by burluiva on 11/11/2023.
//
#include "config_parser_key.h"

void parser_key_init(ParserKey *parserKey) { parserKey->n = 0; }

void parser_key_add_rule(ParserKey *parserKey, int point, int grammarRuleId) {
  assert(parserKey->n + 1 < MAX_SUB_KEYS_NUMBER);
  parserKey->subKeys[parserKey->n].grammarRuleId = grammarRuleId;
  parserKey->subKeys[parserKey->n].point = point;
  parserKey->n = parserKey->n + 1;
}

void parser_key_add_rules_from_grammar(ParserKey *parserKey, bool **used,
                                           TokenType lookForToken,
                                           Grammar *grammar) {
  assert(used && parserKey && grammar);

  for (int j = 0; j < grammar->rulesNumber; j++) {
    if (!used[0][j] && // must be unique/unused in parserKey
        grammar->grammarRules[j].resultTokenType ==
            lookForToken && // must be equal to looked for token
        grammar->grammarRules[j].productionsNumber >
            0 // nullable could not be added
    ) {
      parser_key_add_rule(parserKey, j, 0);
      used[0][j] = true;
      parser_key_add_rules_from_grammar(
          parserKey, used, grammar->grammarRules[j].productions[0], grammar);
    }
  }
}

//TODO parser would be improved using additional first symbols
void parser_key_gen_by_move(ParserKey *destKey, ParserKey *sourceKey,
                            TokenType move, Grammar *grammar) {
  assert(destKey && sourceKey && grammar);
  // [i][j] the i-th point in j-th rule
  bool used[MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE + 1]
           [MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE] = {false};

  for (int i = 0; i < sourceKey->n; i++) {
    struct parser_sub_key_t *subKey = &(sourceKey->subKeys[i]);
    if (grammar->grammarRules[subKey->grammarRuleId].productionsNumber <=
        subKey->point) {
      continue; // point could not move forward just miss this rule
    }

    if (grammar->grammarRules[subKey->grammarRuleId]
            .productions[subKey->point] ==
        move) { // the point of i-th rule could be moved
      if (!used[subKey->point + 1]
               [subKey->grammarRuleId]) { // we don`t need duplicates of the
                                          // rules
        parser_key_add_rule(destKey, subKey->grammarRuleId,
                            subKey->point + 1); // adding rule to the key
        used[subKey->point + 1][subKey->grammarRuleId] = true;

        if (grammar->grammarRules[subKey->grammarRuleId].productionsNumber <=
            subKey->point) {
          continue;
        } // in case if no symbol after, we could not add new rules
          // from grammar

        TokenType lookForToken = grammar->grammarRules[subKey->grammarRuleId]
                                     .productions[subKey->point + 1];
        parser_key_add_rules_from_grammar(destKey, (bool **)used, lookForToken,
                                          grammar);
      }
    }
  }
}