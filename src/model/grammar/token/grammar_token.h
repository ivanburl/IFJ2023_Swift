//
// Created by burluiva on 10/28/2023.
//

#ifndef IFJ2023_SWIFT_GRAMMAR_TOKEN_H
#define IFJ2023_SWIFT_GRAMMAR_TOKEN_H

#include "../../token/token.h"

#define MAX_GRAMMAR_TOKEN_TOKENS_HOLDER_SIZE 128

struct grammar_token_t;

typedef struct grammar_token_t {
  int grammarRuleId;
  int tokensHolderSize;
  Token* tokensHolder[MAX_GRAMMAR_TOKEN_TOKENS_HOLDER_SIZE];
} GrammarToken;

void grammar_token_init(GrammarToken *grammarToken);
void grammar_token_add(GrammarToken *grammarToken, Token *token);
void grammar_token_free(GrammarToken *grammarToken);

#endif // IFJ2023_SWIFT_GRAMMAR_TOKEN_H
