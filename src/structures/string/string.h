//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_STRING_H
#define IFJ2023_SWIFT_STRING_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
  size_t length;
  char *data;
} String;

String string_create(char *cstr);
void string_free(String *str);

#endif // IFJ2023_SWIFT_STRING_H
