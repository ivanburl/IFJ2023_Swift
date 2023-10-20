//
// Created by burluiva on 10/10/2023.
//

#include "token.h"
#include "stdlib.h"

void token_init(Token* token) {
    assert(token);
    token->type = UNDEFINED;
}

Token token_create(TokenType type, char *str) {
  assert(str);

  Token token;
  token.type = type;

  switch (type) {
  case STRING: {
    token.data.string = string_create(str);
    break;
  }
  case INTEGER: {
    token.data.integer_value = strtoll(str, NULL, 10);
    break;
  }
  case DOUBLE: {
    token.data.double_value = strtod(str, NULL);
    break;
  }
  default:
    break;
  }

  return token;
}

void token_free(Token *token) {
  assert(token);
  switch (token->type) {
  case STRING: {
    string_free(&token->data.string);
    break;
  }
  default:
    break;
  }
}