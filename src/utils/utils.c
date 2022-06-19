#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "utils.h"

char *int32ToString(const int32_t n) {
  char *s = malloc(32 + 1);
  sprintf(s, "%" PRId32, n);
  return s;
}

char *int64ToString(const int64_t n) {
  char *s = malloc(64 + 1);
  sprintf(s, "%" PRId64, n);
  return s;
}

int32_t *newInt32(const int32_t n) {
  int32_t *np = malloc(sizeof(int32_t));
  *np = n;
  return np;
}

int64_t *newInt64(const int64_t n) {
  int64_t *np = malloc(sizeof(int64_t));
  *np = n;
  return np;
}
