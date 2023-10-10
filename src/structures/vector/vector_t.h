//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_VECTOR_T_H
#define IFJ2023_SWIFT_VECTOR_T_H

#include "../../utils/util.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define vector_MIN_CAP 128

#define vector_struct(T, N)                                                    \
  typedef struct N##_vector {                                                  \
    T *buf;                                                                    \
    size_t capacity;                                                           \
    size_t size;                                                               \
  } N##Vector;

#define vector_init(T, N)                                                      \
  void N##Vector_init_size(N##Vector *vec, size_t size) {                      \
    assert(vec);                                                               \
    vec->capacity = vector_MIN_CAP > size ? vector_MIN_CAP : size;             \
    vec->size = size;                                                          \
    vec->buf = calloc(sizeof(T), vec->capacity);                               \
    assert(vec->buf);                                                          \
  }                                                                            \
  void N##Vector_init_arr(N##Vector *vec, const T *arr, size_t arr_size) {     \
    assert(vec &&arr &&arr_size > 0);                                          \
    N##Vector_init_size(vec, arr_size);                                        \
    for (size_t i = 0; i < arr_size; i++)                                      \
      vec->buf[i] = arr[i];                                                    \
  }                                                                            \
                                                                               \
  void N##Vector_init(N##Vector *vec) { N##Vector_init_size(vec, 0); }

#define vector_get(T, N)                                                       \
  T N##Vector_get(N##Vector *vec, size_t idx) {                                \
    assert(vec &&idx < vec->size && vec->buf);                                 \
    return vec->buf[idx];                                                      \
  }

#define vector_set(T, N)                                                       \
  void N##Vector_set(N##Vector *vec, size_t idx, T data) {                     \
    assert(vec &&idx < vec->size && vec->buf);                                 \
    vec->buf[idx] = data;                                                      \
  }

#define vector_push(T, N)                                                      \
  void N##Vector_push(N##Vector *vec, T data) {                                \
    assert(vec && vec->buf);                                                   \
    if (vec->size == vec->capacity) {                                          \
      vec->capacity *= 2;                                                      \
      T *tmp = realloc(vec->buf, sizeof(T) * vec->capacity);                   \
      assert(tmp);                                                             \
      vec->buf = tmp;                                                          \
    }                                                                          \
    N##Vector_set(vec, vec->size++, data);                                     \
  }

#define vector_free(T, N)                                                      \
  void N##Vector_free(N##Vector *vec) {                                        \
    assert(vec);                                                               \
    free(vec);                                                                 \
  }

#define vector_remove(T, N)                                                    \
  T N##Vector_remove(N##Vector *vec, size_t pos) {                             \
    assert(vec && vec->buf && vec->size > 0 && pos < vec->size);               \
    T tmp = N##Vector_get(vec, pos);                                           \
    vec->size = vec->size - 1;                                                 \
    for (size_t i = pos; i < vec->size; i++) {                                 \
      swap(vec->buf + i, vec->buf + i + 1, sizeof(T));                         \
    }                                                                          \
    return tmp;                                                                \
  }                                                                            \
  T N##Vector_pop(N##Vector *vec) {                                            \
    assert(vec && vec->size > 0);                                              \
                                                                               \
    return N##Vector_remove(vec, vec->size - 1);                               \
  }                                                                            \
  void N##Vector_clear(N##Vector *vec) {                                       \
    assert(vec);                                                               \
    vec->size = 0;                                                             \
  }

#define vector(T, N)                                                           \
  vector_struct(T, N);                                                         \
  vector_init(T, N) vector_free(T, N) vector_get(T, N) vector_set(T, N)        \
      vector_push(T, N) vector_remove(T, N)

#endif // IFJ2023_SWIFT_VECTOR_T_H
