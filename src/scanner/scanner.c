//
// Created by burluiva on 10/10/2023.
//

#include "scanner.h"


void scanner_init(Scanner *scanner, ScannerAutomataConfigurator configurator) {
  assert(scanner);
  automata_init(&(scanner->automata), SCANNER_DEFAULT_STATE, UNDEFINED);
  configurator(&(scanner->automata));
}

Error scanner_code_to_tokens(Scanner *scanner, char *code,
                             TokenVector *tokenVector) {
  assert(scanner && code && tokenVector);
  size_t code_len = strlen(code);

  char tokenStr[MAX_TOKEN_LENGTH];
  int tokenStrPointer = 0;
  tokenStr[0] = 0;

  TokenType lastTokenTypeRecorded = UNDEFINED;
  int endTokenStrPointer = 0;

  for (size_t i = 0; i < code_len; i++) {
    char feed = code[i];
    // scanner_move_forward(scanner, feed);
    scanner_move_forward(scanner, feed);

    if (scanner->automata.currentState == scanner->automata.startState) {
      assert(lastTokenTypeRecorded == UNDEFINED); // TODO normal error report

      tokenStr[endTokenStrPointer] = 0;
      vector_push_back(tokenVector,
                       token_create(lastTokenTypeRecorded, tokenStr));

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

  return error_create(NONE, NULL);
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
