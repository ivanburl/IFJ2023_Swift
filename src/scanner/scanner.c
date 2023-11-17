//
// Created by burluiva on 10/10/2023.
//

#include "scanner.h"

void scanner_init(Scanner *scanner) {
  assert(scanner);
  automata_init(&(scanner->automata), SCANNER_DEFAULT_STATE, UNDEFINED);
}

Error scanner_code_to_tokens(Scanner *scanner, char *code,
                             TokenVector *tokenVector) {
  assert(scanner && code && tokenVector);
  size_t code_len = strlen(code);

  char tokenStr[1024];//TODO the size of array is small for majority of operations
  int left = 0 , right = 0;
  int tokenStrPointer = 0;
  tokenStr[0] = 0;

  TokenType lastTokenTypeRecorded = UNDEFINED;
  int endTokenStrPointer = 0;

  for (size_t i = 0; i < code_len; i++) {
    char feed = code[i];
    // scanner_move_forward(scanner, feed);
    scanner_move_forward(scanner, feed);

    if (scanner->automata.currentState == scanner->automata.startState) {
      // assert(lastTokenTypeRecorded == UNDEFINED); // TODO normal error report
      if (lastTokenTypeRecorded == UNDEFINED) {
        return error_create(NONE, "undefined token...");
      }

      tokenStr[endTokenStrPointer] = 0;
      Token token;
      Error error = token_create(lastTokenTypeRecorded, tokenStr, &token);
      if (error.errorType != NONE) {
        return error;
      }
      vector_push_back(tokenVector, token);

      tokenStr[0] = 0;
      tokenStrPointer = 0;

      lastTokenTypeRecorded = UNDEFINED;
      endTokenStrPointer = 0;

      scanner_move_forward(scanner, feed);
    }

    tokenStr[tokenStrPointer++] = feed;

    if (scanner_get_currentTokenType(scanner) != UNDEFINED) {
      lastTokenTypeRecorded = scanner_get_currentTokenType(scanner);
      endTokenStrPointer = tokenStrPointer;
    }
  }

  if (lastTokenTypeRecorded == UNDEFINED) {
    return error_create(UNDEFINED_TOKEN, "undefined token...");
  }

  tokenStr[endTokenStrPointer] = 0;
  Token token;
  Error error = token_create(lastTokenTypeRecorded, tokenStr, &token);
  if (error.errorType != NONE) {
    return error;
  }
  vector_push_back(tokenVector, token);

  return error_create(NONE, "finished successfully");
}

void scanner_move_forward(Scanner *scanner, char symbol) {
  assert(scanner);
  automata_next_state(&(scanner->automata), symbol);
}

TokenType scanner_get_currentTokenType(Scanner *scanner) {
  assert(scanner);
  return automata_get_stateReturnValue(&(scanner->automata),
                                       scanner->automata.currentState);
}
