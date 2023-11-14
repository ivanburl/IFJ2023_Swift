//
// Created by burluiva on 10/10/2023.
//

#include "parser.h"
#include "config/config_parser.h"

void parser_init(Parser *parser) {
  assert(parser);
  parser->grammar = NULL;
  automata_init(&(parser->automata), -1, -1);
}

void parser_create(Parser *parser, Grammar *grammar) {
  assert(parser && grammar);
  parser->grammar = grammar;
}

Token parser_parse(Parser *parser, TokenVector *tokenVector) {
  assert(parser && tokenVector);
  // TODO
}

void parser_configure(Parser* parser) {
  assert(parser);
  ifj_2023_parser_config(parser);
}