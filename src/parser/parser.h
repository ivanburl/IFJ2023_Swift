//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_PARSER_H
#define IFJ2023_SWIFT_PARSER_H

#include "../model/grammar/grammar.h"
#include "../structures/automata/automata.h"
#include "ll_parser/ll_parser.h"
#include "precedence_parser/precedence_parser.h"

typedef struct parser_t {
  ///the ll parser is used for statements + expression simplifying
  LLParser *llParser;
  ///used for expression parsing
  PParser *expressionParser;
} Parser;

typedef Error (*ParserConfiguratorFn)(Parser *parser);


void parser_init(Parser *parser);
void parser_configure(ParserConfiguratorFn parserConfiguratorFn);

/// Parse the token vector whit specific offset
/// \param parser configured parser
/// \param resultToken result token which should be the result (the type should be set)
/// \param tokenVector token vector input for parsing
/// \param startOffset from which index of vector to start parsing
/// \param finalOffset the last index of vector which was successfully parsed
/// \return with which error parsing finished
Error parser_parse(Parser *parser, GrammarToken *grammarToken,
                   TokenVector *tokens, int *offset, TokenType finalToken);

#endif // IFJ2023_SWIFT_PARSER_H