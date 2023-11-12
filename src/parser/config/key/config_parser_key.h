//
// Created by burluiva on 11/11/2023.
//

#ifndef IFJ2023_SWIFT_CONFIG_PARSER_KEY_H
#define IFJ2023_SWIFT_CONFIG_PARSER_KEY_H

#include "../../../model/grammar/grammar.h"

#define MAX_SUB_KEYS_NUMBER (MAX_GRAMMAR_RULES_SIZE * 4)

typedef struct parser_sub_key_t {
  int point;
  int grammarRuleId;
} ParserSubKey;

typedef struct parser_key_t {
  /// number of sub keys
  int n;
  ParserSubKey subKeys[MAX_SUB_KEYS_NUMBER];
} ParserKey;

void parser_key_init(ParserKey* parserKey);


/// adds all rules from grammar which define lookForToken
/// add rule in such format S -> .E,
/// where it would recursively add all other rules like
/// E -> .F, E->.T
/// \param parserKey - key to which add rules
/// \param used - the massive of used rules in parser_key
/// \param lookForToken - token
/// \param grammar - grammar from which to find tokens
void parser_key_add_rules_from_grammar(ParserKey *parserKey, bool **used,
                                       TokenType lookForToken,
                                       Grammar *grammar);

/// The generation made by moving point by specific token type
/// \param destKey  the key to which should be generated (must be initialized)
/// \param sourceKey the key from which move is made
/// \param move the toke by which move is executed
/// \param grammar grammar which used during generation
void parser_key_gen_by_move(ParserKey* destKey, ParserKey* sourceKey, TokenType move,
                     Grammar* grammar);


#endif // IFJ2023_SWIFT_CONFIG_PARSER_KEY_H
