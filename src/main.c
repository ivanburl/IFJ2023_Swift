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
  char_vector_init_size(&inputVector, 1000);
//  int c = 0;
//  while ((c = getchar()) != EOF) {
//    char_vector_push_back(&inputVector, (char)c);
//  }
  inputVector.data = "write(10);";

  //  char *code = "var str1 = \"Toto je nejaky text v programu jazyka
  //  IFJ23\"\n"
  //               "let str2 = str1 + \", ktery jeste trochu obohatime\"\n"
  //               "write(str1, \"\\n\", str2, \"\\n\")\n"
  //               "let i = length(str1)\n"
  //               "write(\"Pozice retezce \\\"text\\\" v str2: \", i,
  //               \"\\n\")\n" "write(\"Zadejte serazenou posloupnost vsech
  //               malych pismen a-h, \")\n"
  //               "\n"
  //               "let newInput = readString()\n"
  //               "if let newInput {\n"
  //               "    str1 = newInput\n"
  //               "    while (str1 != \"abcdefgh\") {}\n"
  //               "\n"
  //               "\n"
  //               "\n"

  //  char *code = "let ac = 1 + 2.0\n"
  //               "let bc = 4 * 3.0\n"
  //               "let cc = 20 - 1.0\n"
  //               "let acc = 1.0 + 2\n"
  //               "let bcc = 4.0 * 3\n"
  //               "let ccc = 20.0 - 1\n"
  //               "\n"
  //               "write(ac, \"\\n\", bc, \"\\n\", cc, \"\\n\")\n"
  //               "write(acc, \"\\n\", bcc, \"\\n\", ccc, \"\\n\")";

  // char *code = "func a(_ l) {\n"
  //              "  write(l, \"\\n\")\n"
  //              "}\n"
  //              "\n"
  ////             "let letter = 1; \n"
  //             "a(1)\n";

  //  char *code = "var a = 5\n"
  //               "while (a > 0) {\n"
  //               "  var b = 10\n"
  //               "  while (b > 0) {\n"
  //               "    write(b)\n"
  //               "    b = b - 1\n"
  //               "  }\n"
  //               "  a = a - 1\n"
  //               "}";
  // char *code = "func a(_ a: Int) { write (\"hui\", a)\n } \n"
  //             "a(10)\n"
  //             "\n";
  // char *code = "let input = 65\n"
  //             "let result = chr(input)\n"
  //             "write (result)\n";
  //  char *code = "let a = 10\n"
  //                "while(a>0) { write(a)\n a = a - 1 \n let b = 10\n while
  //                (b>0) { write(b)\n b = b - 1\n } }\n" "write(a, \" test
  //                \")\n";
  // TODO multiple args in fucntion does not work
  // TODO "var a = 10; a = 20;"
  // TODO "write + write"
  // inputVector.data = code;

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
