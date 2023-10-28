//
// Created by burluiva on 10/28/2023.
//

#ifndef IFJ2023_SWIFT_GRAMMAR_TOKEN_H
#define IFJ2023_SWIFT_GRAMMAR_TOKEN_H

#include "../../../structures/vector/vector.h"
#include "../../token/token.h"

#define MAX_GRAMMAR_TOKEN_TOKENS_HOLDER_SIZE 128

/// only non-terminal tokensHolder could be here
typedef enum {
  UNDEFINED_GRAMMAR_TOKEN_TYPE,
  /// S->S;S
  S_SEQUENTIAL,
  /// S->E
  S_EXPRESSION,
  /// E->E+T
  E_SUM,
  /// E -> T
  E_TERMINAL,
  /// T -> T*F
  T_MULTIPLICATION,
  /// T -> F
  T_FACTOR,
  /// F -> ID
  F_ID,
  /// F -> NUM,
  F_NUM,
  /// F -> (E)
  F_BRACKETS
} GrammarTokenType;

typedef struct grammar_token_t {
  GrammarTokenType type;
  int tokensHolderSize;
  Token tokensHolder[MAX_GRAMMAR_TOKEN_TOKENS_HOLDER_SIZE];
} GrammarToken;

void grammar_token_init(GrammarToken* grammarToken);

GrammarToken grammar_token_create(GrammarTokenType type, Token* tokens, int tokensNumber);

#endif // IFJ2023_SWIFT_GRAMMAR_TOKEN_H
