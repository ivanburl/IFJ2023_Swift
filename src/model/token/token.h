//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_TOKEN_H
#define IFJ2023_SWIFT_TOKEN_H

#include "../../structures/string/string.h"

#define MAX_TOKEN_LENGTH 128

typedef enum token_enum {
  UNDEFINED,



  STRING,
  INTEGER,
  DOUBLE,
  NIL,
  MULTI_STRING,
  COMMENT,
  MULTI_COMMENT,

  ID,

  BLANK, DELIMITER,

  STRING_TYPE, INT_TYPE, DOUBLE_TYPE,BOOLEAN_TYPE,
  STRING_NULLABLE_TYPE, INT_NULLABLE_TYPE,DOUBLE_NULLABLE_TYPE,BOOLEAN_NULLABLE_TYPE,

  IF, ELSE,

  LET, VAR,

  WHILE,

  QUOTE, LEFT_CURL_BRACKET, RIGHT_CURL_BRACKET, LEFT_BRACKET, RIGHT_BRACKET,COLON,SEMICOLON,

  PLUS, MINUS, MULTIPLY, DIVIDE,EQUAL,ASSIGN,LESS_EQUAL,GREATER_EQUAL,GREATER,LESS,
  NOT_EQUAL,

  SOFT_UNWRAP, HARD_UNWRAP,

  FUNC, ARROW, COMMA, RETURN, UNDERSCORE

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
