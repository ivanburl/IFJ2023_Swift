//
// Created by burluiva on 10/28/2023.
//

#include "grammar_token.h"
#include "../../../model/token/token.h"

void grammar_token_init(GrammarToken *grammarToken) {
  assert(grammarToken);
  grammarToken->grammarRuleId = -1;
  grammarToken->grammarRule = NULL;
  grammarToken->reg = -1;
  grammarToken->returnType = UNDEFINED;
  grammarToken->isGlobal = false;
  grammarToken->tokensHolderSize = 0;
  for (int i = 0; i < MAX_GRAMMAR_TOKEN_TOKENS_HOLDER_SIZE; i++) {
    grammarToken->tokensHolder[i] = NULL;
  }
}

void grammar_token_add(GrammarToken *grammarToken, Token *token) {
  assert(grammarToken->tokensHolderSize < MAX_GRAMMAR_TOKEN_TOKENS_HOLDER_SIZE);
  grammarToken->tokensHolder[grammarToken->tokensHolderSize++] = token;
}

void grammar_token_free(GrammarToken *grammarToken) {
  assert(grammarToken);
  for (int i = 0; i < grammarToken->tokensHolderSize; i++) {
    if (grammarToken->tokensHolder[i]->type > NON_TERMINAL_UNDEFINED) {
      grammar_token_free(grammarToken->tokensHolder[i]->data.grammarToken);
    }
    free(grammarToken->tokensHolder[i]);
    grammarToken->tokensHolder[i] = NULL;
  }
  grammarToken->tokensHolderSize = 0;
  grammarToken->grammarRuleId = -1;
  grammarToken->grammarRule = NULL;
}
