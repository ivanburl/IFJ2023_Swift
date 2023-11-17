//
// Created by burluiva on 10/12/2023.
//

#ifndef IFJ2023_SWIFT_ERROR_H
#define IFJ2023_SWIFT_ERROR_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_ERROR_MESSAGE 256

typedef enum error_exit_code {
  NONE,
  UNDEFINED_TOKEN,
  FATAL,
  SCANNER_ERROR,
  PARSER_ERROR,
  STRING_PREPROCESS_ERROR
} ErrorType;

typedef struct error_t {
  ErrorType errorType;
  char msg[MAX_ERROR_MESSAGE];
} Error;

Error error_create(ErrorType errorType, char *msg);
Error error_unite(Error errorA, Error errorB);

#endif // IFJ2023_SWIFT_ERROR_H
