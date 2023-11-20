//
// Created by burluiva on 10/12/2023.
//

#include "error.h"
#include "string.h"

// TODO error reporting thing

Error error_create(ErrorType errorType, char *msg) {
  Error error;
  error.errorType = errorType;
  if (msg == NULL) msg = "No error message!\0";
  strcpy(error.msg, msg);
  return error;
}
