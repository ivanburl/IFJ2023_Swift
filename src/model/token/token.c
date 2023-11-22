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
    delete_quotes(&str);
    preprocessError = preprocess_literal_multiString(str);
    if (preprocessError.errorType != NONE)
      return preprocessError;
    //Delete first \n
    str++;
    //skip spaces
    while (*str == ' ')
      str++;

    preprocessError = preprocess_literal_string(str);
    if (preprocessError.errorType != NONE)
      return preprocessError;

    token.data.string = string_create(str);
    break;
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
  case  BOOLEAN: {
    token.data.integer_value = strcmp(str, "false\0") == 0 ? 0 : 1;
    break;
  }
  case DOUBLE: {
    token.data.double_value = strtod(str, NULL);
    break;
  }
  case ID:
    token.data.string = string_create(str);
    break;
  default:
    break;
  }

  *outToken = token;
  return error_create(NONE, "completed");
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

Error preprocess_literal_multiString(char *literal){
  int indent = get_multiLine_indent(literal);
  if (indent == -1)
    return error_create(SCANNER_ERROR, "Error while creating multiline");

  //delete first \n
  literal++;
  //start processing line by line
  int skipLine = 0;
  int indentCount = 0;
  char *current = literal;
  while (*literal) {
    //check if line ends
    if (*literal == '\n') {
      indentCount = 0;
      if (!skipLine) {
        *current = *literal;
        current++;
      }
      skipLine = 0;
      literal++;
      continue;
    }

    //check for indents
    if (*literal == ' ' && indentCount != indent) {
      indentCount++;
      literal++;
      continue;
    }
    if (indentCount != indent)
      return error_create(SCANNER_ERROR, "Bad intends in multi string");

    //check for \\ (usual '\')
    //just send them into string to process later
    if (*literal == '\\' && *(literal+1) == '\\') {
      *current = *literal;
      current++;
      literal++;
      *current = *literal;
      current++;
      literal++;
      continue;
    }

    if (*literal == '\\') {
      //example: word \ \ \n
      if (skipLine)
        return error_create(SCANNER_ERROR, "bad skip line in multi string");
      skipLine = 1;
      literal++;
      continue;
    }

    //example: some word \ another word \n
    if (skipLine && *literal != ' ')
      return error_create(SCANNER_ERROR, "bad skip line in multi string");

    *current = *literal;
    current++;
    literal++;
  }
  //check for last \n
  current--;
  if (*current != '\n')
    return error_create(SCANNER_ERROR, "bad end line in multi string");
  *current = '\0';
  return error_create(NONE, "none");
}

int get_multiLine_indent(char *literal) {
  int indent = 0;
  size_t len = strlen(literal);
  while(literal[--len] == ' ') {
    indent++;
  }

  if (literal[len] != '\n')
    return -1;

  return indent;
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
      return error_create(SCANNER_ERROR, "bad escape sequence");

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
      return error_create(SCANNER_ERROR, "bad escape sequence");
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
    return error_create(SCANNER_ERROR, "bad unicode sequence");
  (*sequence)++;

  while (**sequence != '}') {
    if (**sequence == '\0')
      return error_create(SCANNER_ERROR, "unicode sequence ends to early");

    hexChars[size] = **sequence;
    size++;
    (*sequence)++;
  }
  hexChars[size] = '\0';

  unsigned int c;
  if (sscanf(hexChars, "%x", &c) != 1)
    return error_create(SCANNER_ERROR, "bad unicode number");
  *output = (char)c;

  return error_create(NONE, "none");
}