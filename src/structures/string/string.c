//
// Created by burluiva on 10/10/2023.
//

#include "string.h"

String string_create(char* cstr) {

  String string;
  if (cstr == NULL) {
    string.length = 0;
    string.data = NULL;
    return string;
  }


  string.length = strlen(cstr);
  string.data = malloc(sizeof(char) * (string.length + 1));
  assert(string.data);
  strcpy(string.data, cstr);

  return string;
}


void string_free(String* str) {
  free(str->data);
  str->data = NULL;
  str->length = 0;
}
