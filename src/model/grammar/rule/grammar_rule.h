//
// Created by burluiva on 10/28/2023.
//

#ifndef IFJ2023_SWIFT_GRAMMAR_RULE_H
#define IFJ2023_SWIFT_GRAMMAR_RULE_H

#include "../token/grammar_token.h"

#define MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE 128

typedef struct grammar_rule_t {
  /// non-terminal result token type like S,E,T,F
  TokenType resultTokenType;
  /// specification of non-terminal token like S_SEQUENTIAL, S_EXPRESSION
  GrammarTokenType resultGrammarTokenType;
  /// number of productions in grammar rule
  int productionsNumber;
  /// token types needed to build the specified \p resultTokenType
  TokenType productions[MAX_GRAMMAR_RULE_PRODUCTIONS_SIZE];
} GrammarRule;

void grammar_rule_init(GrammarRule *grammarRule);

GrammarRule grammar_rule_create(TokenType resultTokenType,
                                GrammarTokenType resultGrammarTokenType,
                                const TokenType *tokenProductions,
                                int productionsNumber);

#endif // IFJ2023_SWIFT_GRAMMAR_RULE_H
