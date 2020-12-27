#include "vector.h"
#include "a/array.h"

#include <stdlib.h>

IVector* newIVector() {
  IVector* vec = malloc(sizeof(IVector));
  vec->size = 0;
  vec->_cap = 0;
  vec->data = NULL;
  return vec;
}

void freeIVector(IVector* vec) {
  clearIVector(vec);
  free(vec);
}

void clearIVector(IVector* vec) {
  if (vec->data != NULL)
    free(vec->data);
  vec->size = 0;
  vec->_cap = 0;
}

void appendToIVector(IVector* vec, const int64_t data) {

  const size_t oldCap = vec->_cap;
  const size_t oldSize = vec->size;

  if (oldCap == 0) {
    // Vector is completely new - allocate memory and insert data.
    vec->size = 1;
    vec->_cap = 2;
    vec->data = newI64Array(vec->_cap);
    vec->data[0] = data;
  } else {
    // Vector contains existing data since _cap is not 0.
    if (oldCap == oldSize) {
      // Vector is at full capacity.
      // Reallocate more memory.
      vec->_cap *= 2;
      vec->data = realloc(vec->data, sizeof(int64_t) * vec->_cap);
    }
    // At this point, _cap - size > 0, thus we can add more element to vec->data.
    vec->data[vec->size++] = data;
  }

}

int64_t* newIArrayFromIVector(IVector* vec) {
  const size_t n = vec->size;
  int64_t* arr = newI64Array(n);
  for (size_t i = 0; i < n; ++i)
    arr[i] = vec->data[i];
  return arr;
}

IVector* newIVectorFromIArray(int64_t* data, const size_t n) {

  IVector* vec = malloc(sizeof(IVector));
  vec->size = n;
  vec->_cap = n;
  vec->data = malloc(sizeof(int64_t) * n);

  for (size_t i = 0; i < vec->size; ++i)
    vec->data[i] = data[i];

  return vec;
}
