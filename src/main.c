#include "scanner/scanner.h"
#include <stdio.h>

void test() {
  char* test = "a + b = 10";
  Scanner scanner;
  scanner_init(&scanner);
  scanner_configure_swift_2023(&scanner);

  TokenVector tokenVector;
  vector_init(&tokenVector);
  scanner_code_to_tokens(&scanner, test, &tokenVector);
  TokenType types[1000];

  for (int i=0;i<tokenVector.length;i++) {
    types[i] = tokenVector.data[i].type;
  }
  int a = 10;
}

int main() {
  test();
  return 0;
}
