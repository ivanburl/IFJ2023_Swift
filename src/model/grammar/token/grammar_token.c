//
// Created by burluiva on 10/28/2023.
//

#include "grammar_token.h"

void grammar_token_init(GrammarToken *grammarToken) {
  assert(grammarToken);
  grammarToken->type = UNDEFINED_GRAMMAR_TOKEN_TYPE;
  grammarToken->tokensHolderSize = 0;
  for (int i = 0; i < MAX_GRAMMAR_TOKEN_TOKENS_HOLDER_SIZE; i++) {
    token_init(&grammarToken->tokensHolder[i]);
  }
}

GrammarToken grammar_token_create(GrammarTokenType type, Token *tokens,
                                  int tokensNumber) {
  assert(tokens);
  assert(tokensNumber >= 0 &&
         tokensNumber <= MAX_GRAMMAR_TOKEN_TOKENS_HOLDER_SIZE);

  GrammarToken grammarToken;
  grammar_token_init(&grammarToken);

  grammarToken.type = type;
  grammarToken.tokensHolderSize = tokensNumber;

  for (int i = 0; i < tokensNumber; i++) {
    grammarToken.tokensHolder[i] = tokens[i];
  }

  return grammarToken;
}