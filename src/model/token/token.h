//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_TOKEN_H
#define IFJ2023_SWIFT_TOKEN_H

#include "../../structures/string/string.h"

#define MAX_TOKEN_LENGTH 128
#define MAX_TOKEN_TYPES_NUMBER 128

/*
 * only terminal token could be
 */
typedef enum token_enum {
  ///TERMINALS (should be constructed by scanner)
  UNDEFINED,

  STRING,
  INTEGER,
  DOUBLE,
  NIL,

  ID,

  BLANK, DELIMITER,

  STRING_TYPE, INT_TYPE, DOUBLE_TYPE,BOOLEAN_TYPE,
  STRING_NULLABLE_TYPE, INT_NULLABLE_TYPE,DOUBLE_NULLABLE_TYPE,BOOLEAN_NULLABLE_TYPE,

  IF, ELSE,

  LET, VAR,

  WHILE,

  QUOTE, LEFT_CURL_BRACKET, RIGHT_CURL_BRACKET, LEFT_BRACKET, RIGHT_BRACKET,

  PLUS, MINUS, MULTIPLY, DIVIDE,

  SOFT_UNWRAP, HARD_UNWRAP,

  FUNC, ARROW, COMMA, RETURN,

  UNDER_SCORE,

  ///NON_TERMINALS (should be constructed by parser)
  S,
  E, T, F
} TokenType;

// resolves infinitive include problem... (implementation of cstruct in implementation file)
struct grammar_token_t;

typedef struct token {
  TokenType type;
  union token_data_t {
    long long integer_value;
    double double_value;
    String string;
    struct grammar_token_t* grammarToken;
  } data;
} Token;


void token_init(Token* token);

/// Creates terminal token type by catching the string
/// \param type - type of the token
/// \param str - caught string
/// \return pre-processed token
/// \note
/// \attention return token is not parsed one
Token token_create(TokenType type, char *str);

/// Creates non terminal token from other tokensHolder
/// \param type - type of token
/// \param grammarToken - caught tokensHolder
/// \return pre-processed token (not parsed one)
Token token_grammar_token_create(TokenType type, struct grammar_token_t* grammarToken);

void token_free(Token *token);

#endif // IFJ2023_SWIFT_TOKEN_H
