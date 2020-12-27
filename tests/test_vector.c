#define TEST_NO_MAIN

#include "acutest.h"
#include "a/array.h"
#include "ds/vector.h"

#include <stddef.h>

void test_newIVector(void) {
  IVector* vec = newIVector();
  TEST_CHECK(vec != NULL);
  freeIVector(vec);
}

void test_clearIVector(void) {
  IVector* vec = newIVector();

  TEST_ASSERT(vec != NULL);

  TEST_CHECK(vec->size == 0);
  TEST_CHECK(vec->_cap == 0);
  TEST_CHECK(vec->data == NULL);

  freeIVector(vec);
}

void test_appendToIVector(void) {
  IVector* vec = newIVector();

  TEST_ASSERT(vec != NULL);
  TEST_ASSERT(vec->data == NULL);

  appendToIVector(vec, 43);
  TEST_CHECK(vec->size == 1);
  TEST_CHECK(vec->_cap == 2);

  appendToIVector(vec, 31);
  TEST_CHECK(vec->size == 2);
  TEST_CHECK(vec->_cap == 2);

  freeIVector(vec);
}

void test_newIArrayFromIVector(void) {
  const size_t n = 10;
  IVector* vec = newIVector();

  TEST_ASSERT(vec != NULL);

  for (size_t i = 0; i < n; ++i)
    appendToIVector(vec, i);

  const size_t size = vec->size;

  TEST_CHECK(size == 10);
  TEST_CHECK(vec->_cap == 16);

  int64_t* arr = newIArrayFromIVector(vec);

  i64ArrayCmp(arr, size, vec->data, size);

  free(arr);
  freeIVector(vec);
}
