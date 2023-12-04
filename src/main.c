#include "codegen/codegen.h"
#include "parser/config/config_parser.h"
#include "parser/parser.h"
#include "scanner/scanner.h"

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
//  char_vector_init_size(&inputVector, 10000);
  char_vector_init(&inputVector);
  int c = 0;
  while ((c = getchar()) != EOF) {
    char_vector_push_back(&inputVector, (char)c);
  }
  if (inputVector.length == 0) {
    printf(".IFJcode23\n");
    return 0;
  }
//   char *code = "var a = readInt()\n"
//               "    var b = readInt()\n"
//               "    if a! == b! {\n"
//               "        write(\"eq\")\n"
//               "    } else {\n"
//               "        write(\"ne\")\n"
//               "    }\n";
//   inputVector.data = code;

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
