//
// Created by burluiva on 10/12/2023.
//

#ifndef IFJ2023_SWIFT_LOGGER_H
#define IFJ2023_SWIFT_LOGGER_H

#include <stdio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"

#define LOG_ERROR(MSG) fprintf(stderr, "%s[ERROR] (from func %s)- %s%s", KRED, __func__, MSG, KNRM)
#define LOG_WARN(MSG) fprintf(stderr, "%s[WARN] (from func %s) - %s%s", KYEL, __func__, MSG, KNRM)
#define LOG_INFO(MSG) fprintf(stdout, "%s[INFO] (from func %s) - %s%s", KGRN, __func__, MSG, KNRM)

#endif // IFJ2023_SWIFT_LOGGER_H
