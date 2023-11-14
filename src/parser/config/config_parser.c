//
// Created by burluiva on 10/28/2023.
//

#include "config_parser.h"
#include "../../structures/hashmap/hashmap.h"
#include "key/config_parser_key.h"
#include "../../utils/logger.h"

void ifj_2023_parser_init_state(Parser *parser, ParserKey *root) {
  assert(root && parser && parser->grammar);
  bool used[MAX_GRAMMAR_RULES_SIZE][MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE + 1] = {
      false};
  parser_key_add_rules_from_grammar(root, used, S, parser->grammar);
  parser_key_sort(root);
}

struct hashmap_parser_entry_t {
  struct hashmap_entry entry;
  ParserKey key;
  int parserKeyId; // id of the state in automata
};

int cmpFn(struct hashmap_parser_entry_t *e1,
          struct hashmap_parser_entry_t *e2) {
  if (e1 == e2)
    return 0;
  if (e1 == NULL || e2 == NULL)
    return 1;
  if (e1->key.n != e2->key.n)
    return 1;

  for (int i = 0; i < e1->key.n; i++) {
    if (e1->key.subKeys[i].point != e2->key.subKeys[i].point ||
        e1->key.subKeys[i].grammarRuleId != e2->key.subKeys[i].grammarRuleId) {
      return 1;
    }
  }
  return 0;
}

int add_key_to_map(HashMap *map, int *parserKeyIdGen, ParserKey* parserKey) {
  assert(map && parserKeyIdGen && parserKey);
  struct hashmap_parser_entry_t* entry = malloc(sizeof (struct hashmap_parser_entry_t));
  hashmap_entry_init(entry, parser_key_hash(parserKey));
  entry->key = *parserKey;
  entry->parserKeyId = *parserKeyIdGen;

  struct hashmap_parser_entry_t *found = hashmap_get(map, entry);
  if (found != NULL) {
    free(entry);
    return found->parserKeyId;
  }

  hashmap_put(map, entry);
  *parserKeyIdGen = *parserKeyIdGen + 1;

  return *parserKeyIdGen - 1;
}

void rec_configuration(Parser *parser, ParserKey *parent, int parentKeyId,
                       HashMap *map, int *parserKeyIdGen);

void ifj_2023_parser_config(Parser *parser) {
  assert(parser);
  int parserKeyIdGen = 0;

  HashMap hashMap;
  hashmap_init(&hashMap, (hashmap_cmp_fn)cmpFn);

  ParserKey root;
  parser_key_init(&root);
  ifj_2023_parser_init_state(parser, &root);

  add_key_to_map(&hashMap, &parserKeyIdGen, &root);
  automata_set_stateReturnValue(&(parser->automata), 0, 0);

  rec_configuration(parser, &root, 0, &hashMap, &parserKeyIdGen);
}

void rec_configuration(Parser *parser, ParserKey *parent, int parentKeyId,
                       HashMap *map, int *parserKeyIdGen) {
  assert(parser && parent && map && parserKeyIdGen);
  bool usedTokens[MAX_TOKEN_TYPES_NUMBER];

  ParserKey next;
  for (int i = 0; i < parent->n; i++) {
    int grammarRuleId = parent->subKeys[i].grammarRuleId;
    int grammarRulePoint = parent->subKeys[i].point;

    if (parser->grammar->grammarRules[grammarRuleId].productionsNumber <=
        grammarRulePoint) {
      if (parent->n ==
          1) { // if only one rule left it is definitely return state
        automata_set_stateReturnValue(&(parser->automata), parentKeyId, 1);
      }
      continue;
    }

    TokenType pointToken = parser->grammar->grammarRules[grammarRuleId]
                               .productions[grammarRulePoint];

    if (usedTokens[pointToken])
      continue;
    usedTokens[pointToken] = true;

    parser_key_init(&next);
    parser_key_gen_by_move(&next, parent, pointToken, parser->grammar);
    parser_key_sort(&next);

    int nextKeyId = add_key_to_map(map, parserKeyIdGen, &next);
    automata_set_edge(&(parser->automata), parentKeyId, pointToken, nextKeyId);

    if (automata_get_stateReturnValue(&(parser->automata), nextKeyId) == -1) { // new state was generated, continue linking states
      automata_set_stateReturnValue(&(parser->automata), nextKeyId,
                                    0); // mark return state as continue

      rec_configuration(parser, &next, nextKeyId, map, parserKeyIdGen);
    }
  }
}