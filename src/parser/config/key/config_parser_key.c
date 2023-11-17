//
// Created by burluiva on 11/11/2023.
//
#include "config_parser_key.h"
#include "../../../structures/hashmap/hashmap.h"

void parser_key_init(ParserKey *parserKey) { parserKey->n = 0; }

int parser_key_add_rule(ParserKey *parserKey, int grammarRuleId, int point) {
  assert(parserKey->n + 1 < MAX_SUB_KEYS_NUMBER);
  parserKey->subKeys[parserKey->n].grammarRuleId = grammarRuleId;
  parserKey->subKeys[parserKey->n].point = point;
  parserKey->n = parserKey->n + 1;
  return parserKey->n - 1;
}

///
/// \param destKey - key to which calculate/evaluate first
/// \param sourceSubKey - key fro generation was done
void parser_key_eval_first(ParserSubKey *destKey, ParserSubKey *sourceSubKey,
                           Grammar *grammar) {
  bool lastNullable = true;
  for (int i = sourceSubKey->point + 1;
       lastNullable &&
       i < grammar->grammarRules[sourceSubKey->grammarRuleId].productionsNumber;
       i++) {
    TokenType token =
        grammar->grammarRules[sourceSubKey->grammarRuleId].productions[i];
    lastNullable &= grammar->nullable[token];
    for (int j = 0; j < MAX_TOKEN_TYPES_NUMBER; j++) {
      destKey->first[j] |= grammar->first[token][j];
    }
  }
  for (int i = 0; lastNullable && i < MAX_TOKEN_TYPES_NUMBER; i++) {
    if (sourceSubKey->first[i] == true) {
      lastNullable &= grammar->nullable[i]; // TODO could be replaced by false
                                            // as all terminals non nullable
      destKey->first[i] = true;
    }
  }
}

void parser_key_create_by_token_closure(ParserKey *parserKey,
                                        TokenType closureToken,
                                        Grammar *grammar) {
  int used[MAX_GRAMMAR_RULES_SIZE][MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE + 1] = {
      -1};
  for (int i = 0; i < grammar->rulesNumber; i++) {
    if (grammar->grammarRules[i].resultTokenType == closureToken) {
      used[i][0] = parser_key_add_rule(parserKey, i, 0);
    }
  }
  parser_key_closure(parserKey, grammar, used);
}

// void parser_key_closure_test(
//     ParserKey *parserKey, ParserSubKey *closureSubKey,
//     int used[MAX_GRAMMAR_RULES_SIZE][MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE + 1],
//     Grammar *grammar) {
//   assert(parserKey && grammar);
//
//   for (int j = 0; j < grammar->rulesNumber; j++) {
//     if (!used[j][0] && // must be unique/unused in parserKey
//         grammar->grammarRules[j].resultTokenType ==
//             lookForToken && // must be equal to looked for token
//         grammar->grammarRules[j].productionsNumber >
//             0 // nullable could not be added
//     ) {
//       used[j][0] = parser_key_add_rule(parserKey, j, 0);
//       parser_key_add_rules_from_grammar(
//           parserKey, used, grammar->grammarRules[j].productions[0], grammar);
//     }
//   }
// }

void parser_key_closure(
    ParserKey *parserKey, Grammar *grammar,
    int used[MAX_GRAMMAR_RULES_SIZE][MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE + 1]) {
  for (int i = 0; i < parserKey->n; i++) {
    ParserSubKey *subKey = &(parserKey->subKeys[i]);
    if (subKey->point >=
        grammar->grammarRules[subKey->grammarRuleId].productionsNumber)
      continue;
    TokenType lookForToken =
        grammar->grammarRules[subKey->grammarRuleId].productions[subKey->point];

    for (int j = 0; j < MAX_TOKEN_TYPES_NUMBER; j++) {
      if (grammar->grammarRules[j].resultTokenType == lookForToken) {
        if (used[j][0] == -1) {
          used[j][0] = parser_key_add_rule(parserKey, j, 0);
        }
        parser_key_eval_first(&(parserKey->subKeys[used[j][0]]), subKey,
                              grammar);
      }
    }
  }
}

// TODO parser would be improved using additional first symbols
void parser_key_gen_by_move(ParserKey *destKey, ParserKey *sourceKey,
                            TokenType move, Grammar *grammar) {
  assert(destKey && sourceKey && grammar);
  // [i][j] the i-th grammar rule id, the j-th is grammar production size
  int used[MAX_GRAMMAR_RULES_SIZE][MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE + 1] = {
      -1};

  for (int i = 0; i < sourceKey->n; i++) {
    struct parser_sub_key_t *subKey = &(sourceKey->subKeys[i]);

    if (grammar->grammarRules[subKey->grammarRuleId]
            .productions[subKey->point] != move) {
      continue;
    }

    if (grammar->grammarRules[subKey->grammarRuleId].productionsNumber <=
        subKey->point) {
      continue;
    }

    if (used[subKey->grammarRuleId][subKey->point + 1] == -1) {
      used[subKey->grammarRuleId][subKey->point + 1] = parser_key_add_rule(
          destKey, subKey->grammarRuleId, subKey->point + 1);
    }
  }

  parser_key_closure(destKey, grammar, used);
}

int parser_sub_key_cmpFn(const ParserSubKey *a, const ParserSubKey *b) {
  int res = a->grammarRuleId - b->grammarRuleId;
  if (res == 0)
    res = a->point - b->point;
  return res;
}

void parser_key_sort(ParserKey *parserKey) {
  qsort(parserKey->subKeys, parserKey->n, sizeof(ParserSubKey),
        (__compar_fn_t)parser_sub_key_cmpFn);
}

#define FNV32_BASE ((unsigned int)0x811c9dc5)
#define FNV32_PRIME ((unsigned int)0x01000193)
unsigned int parser_key_hash(ParserKey *parserKey) {
  unsigned int hash = FNV32_BASE;
  unsigned int base = (1 << 8) - 1;

  for (int i = 0; i < 4; i++, base <<= 8) {
    hash = hash * FNV32_PRIME;
    hash = hash ^ (base & (unsigned int)parserKey->n);
    for (int j = 0; j < parserKey->n; j++) {
      hash = hash * FNV32_PRIME;
      hash = hash ^ (base & (unsigned int)parserKey->subKeys[i].point);
      hash = hash * FNV32_PRIME;
      hash = hash ^ (base & (unsigned int)parserKey->subKeys[i].grammarRuleId);
    }
  }
  return hash;
}
