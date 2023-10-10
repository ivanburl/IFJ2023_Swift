//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_SCANNER_H
#define IFJ2023_SWIFT_SCANNER_H

#include "../model/token/token.h"
#include "../structures/vector/vector_t.h"
#include <limits.h>

vector(Token, Token);

#define MAX_SCANNER_STATES 64

typedef struct scanner {
  int current_state;
  int automata[MAX_SCANNER_STATES][CHAR_MAX + 1];
} Scanner;

void scanner_init(Scanner* scanner);
void configure_automata(Scanner* scanner);
TokenVector scan_code(char *text);

#endif // IFJ2023_SWIFT_SCANNER_H
