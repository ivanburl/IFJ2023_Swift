//
// Created by burluiva on 10/10/2023.
//

#include "token.h"
#include "../grammar/token/grammar_token.h"
#include "stdlib.h"
#include <stdio.h>

void token_init(Token *token) {
  assert(token);
  token->type = UNDEFINED;
}

Error token_create(TokenType type, char *str, Token *outToken) {
  assert(str);

  Token token;
  token.type = type;

  Error preprocessError;
  switch (type) {
  case MULTI_STRING:
  case STRING: {
    //delete leading and trailing quotes
    delete_quotes(&str);

    //preprocess string
    preprocessError = preprocess_literal_string(str);
    if (preprocessError.errorType != NONE)
      return preprocessError;

    //create token
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

  *outToken = token;
}

Token token_grammar_token_create(TokenType type,
                                 struct grammar_token_t *grammarToken) {
  Token token;
  token_init(&token);
  token.type = type;
  token.data.grammarToken = grammarToken;
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

void delete_quotes(char **str) {
  while (**str == '"')
    (*str)++;
  size_t len = strlen(*str);

  while (len > 0 && (*str)[len-1] == '"')
    (*str)[--len] = '\0';
}

Error preprocess_literal_string(char *literal) {
  char *current = literal;

  while (*literal) {
    if (*literal != '\\') {
      *current = *literal;
      current++;
      literal++;
      continue;
    }

    literal++;
    if (*literal == '\0')
      return error_create(STRING_PREPROCESS_ERROR, "bad escape sequence");

    Error unicodeError;
    switch (*literal) {
    case 'n':
      *current = '\n';
      break;
    case '0':
      *current = '\0';
      break;
    case '\\':
      *current = '\\';
      break;
    case 't':
      *current = '\t';
      break;
    case '"':
      *current = '"';
      break;
    case '\'':
      *current = '\'';
      break;
    case 'u':
      unicodeError = process_unicode(&literal, current);
      if (unicodeError.errorType != NONE)
        return unicodeError;
      break;
    default:
      return error_create(STRING_PREPROCESS_ERROR, "bad escape sequence");
    }
    current++;
    literal++;
  }
  *current = '\0';
  return error_create(NONE, "none");
}

Error process_unicode(char **sequence, char *output) {
  char hexChars[8];
  int size = 0;
  (*sequence)++;
  if (**sequence != '{')
    return error_create(STRING_PREPROCESS_ERROR, "bad unicode sequence");
  (*sequence)++;

  while (**sequence != '}') {
    if (**sequence == '\0')
      return error_create(STRING_PREPROCESS_ERROR, "unicode sequence ends to early");

    hexChars[size] = **sequence;
    size++;
    (*sequence)++;
  }
  hexChars[size] = '\0';

  unsigned int c;
  if (sscanf(hexChars, "%x", &c) != 1)
    return error_create(STRING_PREPROCESS_ERROR, "bad unicode number");
  *output = (char)c;

  return error_create(NONE, "none");
}