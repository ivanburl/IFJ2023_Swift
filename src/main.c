#include "codegen/codegen.h"
#include "parser/config/config_parser.h"
#include "parser/parser.h"
#include "scanner/scanner.h"

#include <stdio.h>

void exportLLTable(Parser* parser);
void exportLRTable(Parser* parser);

int main() {
  Error err;
  err.errorType = NONE;

  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

freopen("../IO/input.txt", "r", stdin);
freopen("../IO/output.txt", "w", stdout);

  Parser parser;
  parser_init(&parser);
  ifj_2023_parser_config(&parser);

  CharVector inputVector;
  char_vector_init(&inputVector);
  int c = 0;
  while ((c = getchar()) != EOF) {
    char_vector_push_back(&inputVector, (char)c);
  }

//  char_vector_push_back(&inputVector, '\n');//TODO without ending line it fails why????


  if (inputVector.length == 0) {
    printf(".IFJcode23\n");
    return 0;
  }
  TokenVector tokenVector;
  token_vector_init(&tokenVector);
  err = scanner_code_to_tokens(&scanner, inputVector.data, &tokenVector);

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
  sem_analyse_start(&sts);
  generate_inter_code(&sts);
  //exportLLTable(&parser);
  return 0;
}

void exportLLTable(Parser* parser) {
  char* names[] = {
    "UNDEFINED", "STRING", "INTEGER",
      "DOUBLE", "NIL", "MULTILINE_STRING",
      "COMMENT", "MULTILINE_COMMENT",
      "BOOLEAN", "ID",
      "BLANK", "DELIMITER", "STRING_TYPE",
      "INT_TYPE", "DOUBLE_TYPE", "BOOLEAN_TYPE",
      "STRING_NULLABLE_TYPE", "INT_NULLABLE_TYPE",
      "DOUBLE_NULLABLE_TYPE", "BOOLEAN_NULLABLE_TYPE",
      "IF", "ELSE", "LET", "VAR", "CONTINUE",
      "BREAK", "WHILE", "LEFT_CURL_BRACKET", "RIGHT_CURL_BRACKET",
      "LEFT_BRACKET", "RIGHT_BRACKET",
      "COLON", "SEMICOLON",
      "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
      "EQUAL", "ASSIGN", "LESS_EQUAL", "GREATER_EQUAL",
      "GREATER", "LESS", "NOT_EQUAL",
      "SOFT_UNWRAP", "HARD_UNWRAP",
      "FUNC", "ARROW", "COMMA", "RETURN",
      "UNDERSCORE", "LOGICAL_AND", "LOGICAL_OR",
      "ID_AND_ASSIGN", "ID_AND_COLON", "VOID_TYPE",
      "NIL_TYPE", "DOLLAR", "NON_TERMINAL_UNDEFINED",
      "S", "E", "F", "STS", "STS_TMP",
      "COND", "BLOCK", "IF_ELSE", "D",
      "ID_INIT", "PARAM", "FUNC_ID",
      "PARAMS", "PARAMS_TMP", "TANN", "TYPE",
      "F_CALL", "ARGS", "ARGS_TMP",
      "ARG", "FUNC_RETURN", "ID_INIT_ASSIGN",
      "E_NULLABLE"
  };
  printf(" ");
  for (int j=0;j<NON_TERMINAL_UNDEFINED;j++)
    printf(",%s", names[j]);
  printf("\n");
  for (int i=NON_TERMINAL_UNDEFINED+1;i<=E_NULLABLE;i++) {
    printf(",%s", names[i]);
    for (int j = 0; j < NON_TERMINAL_UNDEFINED; j++) {
      if (parser->llParser->llTable[i][j] == -1)
        printf(",x");
      if (parser->llParser->llTable[i][j] != -1)
        printf(",%d", parser->llParser->llTable[i][j]);
    }
    printf("\n");
  }
}
