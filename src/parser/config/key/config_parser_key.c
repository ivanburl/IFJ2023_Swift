//
// Created by burluiva on 11/11/2023.
//
#include "config_parser_key.h"
#include "../../../structures/hashmap/hashmap.h"

void parser_key_init(ParserKey *parserKey) { parserKey->n = 0; }

void parser_key_add_rule(ParserKey *parserKey, int grammarRuleId,  int point) {
  assert(parserKey->n + 1 < MAX_SUB_KEYS_NUMBER);
  parserKey->subKeys[parserKey->n].grammarRuleId = grammarRuleId;
  parserKey->subKeys[parserKey->n].point = point;
  parserKey->n = parserKey->n + 1;
}

void parser_key_add_rules_from_grammar(
    ParserKey *parserKey,
    bool used[MAX_GRAMMAR_RULES_SIZE][MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE + 1],
    TokenType lookForToken, Grammar *grammar) {
  assert(parserKey && grammar);

  for (int j = 0; j < grammar->rulesNumber; j++) {
    if (!used[j][0] && // must be unique/unused in parserKey
        grammar->grammarRules[j].resultTokenType ==
            lookForToken && // must be equal to looked for token
        grammar->grammarRules[j].productionsNumber >
            0 // nullable could not be added
    ) {
      parser_key_add_rule(parserKey, j, 0);
      used[j][0] = true;
      parser_key_add_rules_from_grammar(
          parserKey, used, grammar->grammarRules[j].productions[0], grammar);
    }
  }
}

// TODO parser would be improved using additional first symbols
void parser_key_gen_by_move(ParserKey *destKey, ParserKey *sourceKey,
                            TokenType move, Grammar *grammar) {
  assert(destKey && sourceKey && grammar);
  // [i][j] the i-th point in j-th rule
  bool used[MAX_GRAMMAR_RULES_SIZE][MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE + 1] = {
      false};

  for (int i = 0; i < sourceKey->n; i++) {
    struct parser_sub_key_t *subKey = &(sourceKey->subKeys[i]);
    if (grammar->grammarRules[subKey->grammarRuleId].productionsNumber <=
        subKey->point) {
      continue; // point could not move forward just miss this rule
    }

    if (grammar->grammarRules[subKey->grammarRuleId]
            .productions[subKey->point] ==
        move) { // the point of i-th rule could be moved
      if (!used[subKey->grammarRuleId]
               [subKey->point + 1]) { // we don`t need duplicates of the
                                          // rules
        parser_key_add_rule(destKey, subKey->grammarRuleId,
                            subKey->point + 1); // adding rule to the key
        used[subKey->grammarRuleId][subKey->point + 1] = true;

        if (grammar->grammarRules[subKey->grammarRuleId].productionsNumber <=
            subKey->point) {
          continue;
        } // in case if no symbol after, we could not add new rules
          // from grammar

        TokenType lookForToken = grammar->grammarRules[subKey->grammarRuleId]
                                     .productions[subKey->point + 1];
        parser_key_add_rules_from_grammar(destKey, used, lookForToken,
                                          grammar);
      }
    }
  }
}

int parser_sub_key_cmpFn(const ParserSubKey* a,const ParserSubKey* b) {
  int res = a->grammarRuleId - b->grammarRuleId;
  if (res == 0) res = a->point - b->point;
  return res;
}

void parser_key_sort(ParserKey* parserKey) {
  qsort(parserKey->subKeys, parserKey->n, sizeof (ParserSubKey),
        (__compar_fn_t)parser_sub_key_cmpFn);
}

#define FNV32_BASE ((unsigned int)0x811c9dc5)
#define FNV32_PRIME ((unsigned int)0x01000193)
unsigned int parser_key_hash(ParserKey* parserKey) {
  unsigned int hash = FNV32_BASE;
  unsigned int base = (1<<8)-1;

  for (int i=0;i<4;i++,base<<=8) {
    hash = hash * FNV32_PRIME;
    hash = hash ^ (base & (unsigned int) parserKey->n);
    for (int j=0;j<parserKey->n;j++) {
      hash = hash * FNV32_PRIME;
      hash = hash ^ (base & (unsigned int) parserKey->subKeys[i].point);
      hash = hash * FNV32_PRIME;
      hash = hash ^ (base & (unsigned int) parserKey->subKeys[i].grammarRuleId);
    }
  }
  return hash;
}

