//
// Created by burluiva on 10/10/2023.
//

#include "scanner.h"

void scanner_init(Scanner *scanner) {
  scanner->current_state = 0;
  for (int i = 0; i < MAX_SCANNER_STATES; i++)
    for (int j = 0; j < CHAR_MAX; j++) {
      scanner->automata[i][j] = 0;
    }
}

TokenVector scan_code(char *text) {
  TokenVector tokenVector;
  TokenVector_init(&tokenVector);
  return tokenVector;
}

void configure_automata(Scanner *scanner) {}