#include "../../scanner/scanner.h"
#include "../scanner_test/scanner_test.h"
#include "../../scanner/configs/ifj23_swift_configurator.h"
#include <stdio.h>
//Норм кенты и так знают что у них нихуя не работает

int test_if_token() {
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char* code = "if";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];

  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == IF);
  printf("Test if_token passed.\n");
}

int test_number_token() {
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char *code = "9890";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];

  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == INTEGER);
  printf("Test int_token passed.\n");
}

int test_id_token(){
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char* code = "naa_irll_03_aad09_hj";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];

  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == ID);
  printf("Test id_token passed.\n");
}

int test_escape_sequences(){
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char *code = "\"hello \\u{53} ta\\tb \\n New Line\"";
  scanner_code_to_tokens(&scanner, code, &tokenVector);

  char *exampleString = "hello S ta\tb \n New Line";
  char *curChar = tokenVector.data[0].data.string.data;
  while (*curChar && *exampleString) {
    assert(*curChar == *exampleString);
    exampleString++;
    curChar++;
  }

  printf("Test escape_sequences passed.\n");
}
/*
int test_unite() {
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);

  //char* code = "if (x > 0) {print(\"Hello,World!\")}";
  //char* code = " > ";
  //Error res = scanner_code_to_tokens(&scanner, code, &tokenVector);
  //printf("Finished with type: %d msg: %s", res.errorType, res.msg);

  TokenType types[1000];
  for (int i =0; i < 1000;i++) {
    types[i] = UNDEFINED;
  }
  for (size_t i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  char* code = "if (x > 0) {print(\"Hello,World!\")}";

  TokenType expectedTypes[] = {IF, BLANK,LEFT_BRACKET, ID,BLANK, GREATER, BLANK, INTEGER, RIGHT_BRACKET, BLANK, LEFT_CURL_BRACKET, ID, LEFT_BRACKET,STRING, RIGHT_BRACKET, RIGHT_CURL_BRACKET};
  size_t expectedLength = sizeof(expectedTypes) / sizeof(expectedTypes[0]);

  assert(tokenVector.length == expectedLength);

  for (size_t i = 0; i < tokenVector.length; i++) {
    if (tokenVector.data[i].type != expectedTypes[i]) {
      printf("Несоответствие на индексе %zu: Ожидалось %d, Получено %d\n", i, expectedTypes[i], tokenVector.data[i].type);
    }
    assert(tokenVector.data[i].type == expectedTypes[i]);
  }


  printf("Test unite passed.\n");
}
*/
int test_let_token() {
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char* code = "let12";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];

  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == LET);
  printf("Test let_token passed.\n");
}

int test_var_token() {
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char* code = "var";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];

  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == VAR);
  printf("Test var_token passed.\n");
}

int test_string() {
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);


  char *code = "\"\"\"Hello,World\"\"\"";
  Error res = scanner_code_to_tokens(&scanner, code, &tokenVector);
  printf("Finished with type: %d msg: %s", res.errorType, res.msg);
  TokenType types[1000] = {UNDEFINED};
  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == MULTI_STRING);
  printf("Test string_token passed.\n");
}

int test_double(){
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char *code= "1.e45";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];
  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == DOUBLE);
  printf("Test double_token passed.\n");
}

int test_double_nul(){
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char *code= "1.e45?";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];
  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == DOUBLE);assert(tokenVector.length == 1);
  assert(types[0] == DOUBLE);
  printf("Test double_nl_token passed.\n");
}

int test_while(){
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char *code= "while";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];
  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == WHILE);
  printf("Test while_token passed.\n");
}

int test_delimiter(){
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  char *code= "\n";
  scanner_code_to_tokens(&scanner, code, &tokenVector);
  TokenType types[1000];
  for (int i = 0; i < tokenVector.length; i++) {
    types[i] = tokenVector.data[i].type;
  }
  assert(tokenVector.length == 1);
  assert(types[0] == DELIMITER);
  printf("Test delimiter_token passed.\n");
}

int main() {

  //test_unite();
  test_double_nul();
  test_delimiter();
  test_id_token();
  test_escape_sequences();
  test_number_token();
  test_if_token();
  test_let_token();
  test_while();
  test_double();
  test_var_token();
  test_string();
  return 0;
}