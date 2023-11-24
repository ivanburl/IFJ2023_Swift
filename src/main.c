#include "parser/config/config_parser.h"
#include "parser/parser.h"
#include "scanner/scanner.h"
#include "codegen/codegen.h"

#include <stdio.h>

int main() {
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  Parser parser;
  parser_init(&parser);
  ifj_2023_parser_config(&parser);

  CharVector inputVector;
  char_vector_init(&inputVector);
  int c = 0;
  while((c = getchar()) != EOF) {
    char_vector_push_back(&inputVector, (char) c);
  }

  TokenVector tokenVector;
  token_vector_init(&tokenVector);
  scanner_code_to_tokens(&scanner, inputVector.data, &tokenVector);

  GrammarToken sts;
  grammar_token_init(&sts);
  int offset = 0;
  parser_parse(&parser, &sts, &tokenVector, &offset, STS, LL_PARSER);

  generate_inter_code(&sts);
  //TODO free memory
  return 0;
}
