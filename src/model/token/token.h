//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_TOKEN_H
#define IFJ2023_SWIFT_TOKEN_H

#include "../../structures/string/string.h"
typedef enum token_enum {
  UNDEFINED,

  STRING,
  INTEGER,
  DOUBLE,

  ID,
  FREE,

  BLANK
} TokenType;

typedef struct token {
  TokenType type;
  union {
    long long integer_value;
    double double_value;
    String string;
  } data;
} Token;

void token_init(Token* token);
Token token_create(TokenType type, char *str);

void token_free(Token *token);

#endif // IFJ2023_SWIFT_TOKEN_H
