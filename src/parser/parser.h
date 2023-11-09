//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_PARSER_H
#define IFJ2023_SWIFT_PARSER_H

#include "../model/grammar/grammar.h"
#include "../structures/automata/automata.h"

typedef struct parser_t {
  Grammar *grammar;
  Automata automata;
} Parser;

void parser_init(Parser *parser);
Parser parser_create(Grammar *grammar);

Token parser_parse(Parser *parser, TokenVector *tokenVector);

#endif // IFJ2023_SWIFT_PARSER_H
