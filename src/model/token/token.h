//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_TOKEN_H
#define IFJ2023_SWIFT_TOKEN_H

#include "../../structures/string/string.h"
#include "../error/error.h"
#include "../../structures/vector/vector_t.h"

#define MAX_TOKEN_TYPES_NUMBER 128

/*
 * only terminal token could be
 */
typedef enum token_enum {
  /// TERMINALS (should be constructed by scanner)
  UNDEFINED,

  STRING,
  INTEGER,
  DOUBLE,
  NIL,
  MULTI_STRING,
  COMMENT,
  MULTI_COMMENT,
  BOOLEAN,

  ID,

  BLANK,
  DELIMITER,

  STRING_TYPE,
  INT_TYPE,
  DOUBLE_TYPE,
  BOOLEAN_TYPE,
  STRING_NULLABLE_TYPE,
  INT_NULLABLE_TYPE,
  DOUBLE_NULLABLE_TYPE,
  BOOLEAN_NULLABLE_TYPE,

  IF,
  ELSE,

  LET,
  VAR,
  CONTINUE,
  BREAK,

  WHILE,

  //QUOTE,
  LEFT_CURL_BRACKET,
  RIGHT_CURL_BRACKET,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  COLON,
  SEMICOLON,

  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  EQUAL,
  ASSIGN,
  LESS_EQUAL,
  GREATER_EQUAL,
  GREATER,
  LESS,
  NOT_EQUAL,

  SOFT_UNWRAP,
  HARD_UNWRAP,

  FUNC,
  ARROW,
  COMMA,
  RETURN,
  UNDERSCORE,
  LOGICAL_AND,
  LOGICAL_OR,

  ///used only for PSA algo
  DOLLAR,

  /// NON_TERMINALS (should be constructed by parser)
  /// tokeType < NON_TERMINAL -> terminal, tokeType > NON_TERMINAL - non-terminal
  NON_TERMINAL_UNDEFINED, //the start of non-terminal symbols

  ///one statements
  S,
  ///expression
  E,
  /// factor of expression
  F,
  /// collection of statements
  STS,
  /// collection of statements (USED FOR LL)
  STS_TMP,
  /// CONDITION
  COND,
  /// BLOCK
  BLOCK,
  /// ELSE part of if statement
  IF_ELSE,
  /// declaration
  D,
  /// parameter for the function (declaration)
  PARAM,
  /// specific case for declaration functions (_ || id)
  FUNC_ID,
  /// collection of params
  PARAMS,
  ///collection of params (USED FOR LL)
  PARAMS_TMP,
  /// annotation of the type (Example = id : Integer), could not be null
  TANN,
  /// annotation of the type (could be nullable)
  TANN_NULL,
  TYPE,
  /// initialisation of the variable, constant
  INIT,
  /// call of function inside expression
  F_CALL,
  /// collection of arguments (calling function)
  ARGS,
  /// collection of arguments (calling function) (USED FOR LL)
  ARGS_TMP,
  /// function argument (calling function)
  ARG,
} TokenType;

struct grammar_token_t;

typedef struct token {
  TokenType type;
  union token_data_t {
    long long integer_value;
    double double_value;
    String string;
    struct grammar_token_t *grammarToken;
  } data;
} Token;

void token_init(Token *token);

/// Creates terminal token type by catching the string
/// \param type - type of the token
/// \param str - caught string
/// \return pre-processed token
/// \note
/// \attention return token is not parsed one
Error token_create(TokenType type, char *str, Token *outToken);

/// Creates non terminal token from other tokensHolder
/// \param type - type of token
/// \param grammarToken - caught tokensHolder
/// \return pre-processed token (not parsed one)
Token token_grammar_token_create(TokenType type,
                                 struct grammar_token_t *grammarToken);

void token_free(Token *token);

void delete_quotes(char **str);
Error preprocess_literal_multiString(char *literal);
int get_multiLine_indent(char *literal);
Error preprocess_literal_string(char *literal);
Error process_unicode(char **sequence, char *output);

#endif // IFJ2023_SWIFT_TOKEN_H
