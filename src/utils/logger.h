//
// Created by burluiva on 10/12/2023.
//

#ifndef IFJ2023_SWIFT_LOGGER_H
#define IFJ2023_SWIFT_LOGGER_H

#include <stdarg.h>
#include <stdio.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"

#define LOG_ERROR(...) log_error(__func__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) log_warn(__func__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) log_info(__func__, __FILE__, __LINE__, __VA_ARGS__)

void log_error(const char *func, const char *file, int line, const char *format,
               ...) {
  va_list args;
  va_start(args, format);

  fprintf(stderr, "%s[ERROR] (from func %s in file %s at line %d) - ", KRED,
          func, file, line);
  vfprintf(stderr, format, args);
  fprintf(stderr, "%s\n", KNRM);

  va_end(args);
}

void log_warn(const char *func, const char *file, int line, const char *format,
              ...) {
  va_list args;
  va_start(args, format);

  fprintf(stderr, "%s[WARN] (from func %s in file %s at line %d) - ", KYEL,
          func, file, line);
  vfprintf(stderr, format, args);
  fprintf(stderr, "%s\n", KNRM);

  va_end(args);
}

void log_info(const char *func, const char *file, int line, const char *format,
              ...) {
  va_list args;
  va_start(args, format);

  fprintf(stderr, "%s[INFO] (from func %s in file %s at line %d) - ", KGRN,
          func, file, line);
  vfprintf(stderr, format, args);
  fprintf(stderr, "%s\n", KNRM);

  va_end(args);
}

#endif // IFJ2023_SWIFT_LOGGER_H
