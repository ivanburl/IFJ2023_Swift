//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_VECTOR_H
#define IFJ2023_SWIFT_VECTOR_H

#include "../../model/token/token.h"
#include "vector_t.h"

vector(Token, Token);
vector(char, Char);
vector(int, Int);
vector(long long, Long);

void test() {
  LongVector longVector;
  LongVector_push(&longVector, 10l);
}

#endif // IFJ2023_SWIFT_VECTOR_H
