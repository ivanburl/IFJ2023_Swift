#include "parser/config/config_parser.h"
#include "parser/parser.h"
#include "scanner/scanner.h"
#include "codegen/codegen.h"

#include <stdio.h>

int main() {
  Error err;
  err.errorType = NONE;

  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  Parser parser;
  parser_init(&parser);
  ifj_2023_parser_config(&parser);

  CharVector inputVector;
  char_vector_init_size(&inputVector, 1000);
//  int c = 0;
//  while((c = getchar()) != EOF) {
//    char_vector_push_back(&inputVector, (char) c);
//  }

//  char* code = "let a = 10\n"
//               "while a != 10 { }\n"
//               "write(\"Ended with \")\n"
//               "\n";

  char *code = "write(\"Ended with\\n\")\n"
               "write(\"Ended with\\n\")\n";

  //TODO multiple args in fucntion does not work
  //TODO "var a = 10; a = 20;"
  //TODO "write + write"
  inputVector.data = code;

  TokenVector tokenVector;
  token_vector_init(&tokenVector);
  err = scanner_code_to_tokens(&scanner, inputVector.data, &tokenVector);

//  TokenType types1[1000];
//
//  for (int i = 0; i < tokenVector.length; i++) {
//    types1[i] = tokenVector.data[i].type;
//  }
//  printf("%d\n", types1[0]);

  if (err.errorType != NONE) {
    error_report(err);
    return err.errorCode;
  }

  GrammarToken sts;
  grammar_token_init(&sts);
  int offset = 0;
  err = parser_parse(&parser, &sts, &tokenVector, &offset, STS, LL_PARSER);

  if (err.errorType != NONE) {
    error_report(err);
    return err.errorCode;
  }

  generate_inter_code(&sts);
  return 0;
}
