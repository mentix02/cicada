#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vector.h"

#define VECTOR_MIN_CAP   2
#define VECTOR_GROW_RATE 2

static bool growVector(struct Vector *vector) {
  void** largerData;
  size_t newCap = vector->cap * VECTOR_GROW_RATE;

  if (vector->data == NULL || newCap == 0) {
    vector->cap = VECTOR_MIN_CAP + 1;
    vector->data = malloc(sizeof(void*) * vector->cap);
    return vector->data != NULL;
  }

  largerData = malloc(sizeof(void*) * newCap);
  memcpy(largerData, vector->data, sizeof(void*) * vector->len);

  free(vector->data);
  vector->cap = newCap;
  vector->data = largerData;

  return true;
}

struct Vector *newVector() {
  struct Vector *vector = malloc(sizeof(struct Vector));
  if (vector == NULL) return NULL;

  vector->len = 0;
  vector->cap = 2;
  vector->data = malloc(sizeof(void*) * vector->cap);

  return vector;
}

struct Vector *newVectorReserved(const size_t n) {
  struct Vector *vector = malloc(sizeof(struct Vector));
  if (vector == NULL) return NULL;

  vector->len = 0;
  vector->cap = n;
  vector->data = malloc(sizeof(void*) * n);

  return vector;
}

void freeVector(struct Vector *vector) {
  cleanVector(vector);
  free(vector->data);
  free(vector);
}

void cleanVector(struct Vector *vector) {
  size_t i;
  for (i = 0; i < vector->len; ++i)
    free(vector->data[i]);
  vector->len = 0;
}

void *lPopVectorEl(struct Vector *vector) {
  size_t i;
  void *dataToReturn;

  assert(vector->len > 0);

  dataToReturn = vector->data[0];

  for (i = 0; i < vector->len-1; ++i) {
    vector->data[i] = vector->data[i+1];
  }

  vector->len--;
  return dataToReturn;
}

void *rPopVectorEl(struct Vector *vector) {
  assert(vector->len > 0);
  return vector->data[--vector->len];
}

bool lPushVectorEl(struct Vector *vector, void *data) {
  size_t i, newCap;
  void **largerData;

  if (vector->len >= vector->cap) {
    newCap = vector->cap * VECTOR_GROW_RATE;

    // allocate memory for bigger array
    largerData = malloc(sizeof(void*) * newCap);

    // copy old contents of vector data array into
    // new, larger array but with an offset of 1
    // for largerData
    memcpy(largerData+1, vector->data, sizeof(void*) * vector->len);
    largerData[0] = data;

    free(vector->data);
    vector->cap = newCap;
    vector->data = largerData;

    return true;
  }

  for (i = vector->len; i > 0; --i)
    vector->data[i] = vector->data[i-1];

  vector->data[0] = data;
  return true;
}

bool rPushVectorEl(struct Vector *vector, void *data) {
  if (vector->len == vector->cap)
    if (!growVector(vector))
      return false;
  vector->data[vector->len++] = data;
  return true;
}

void *getVectorEl(struct Vector *vector, const size_t n) {
  if (n >= vector->len) {
    printf("warning: trying to read el #%zu from vector of size %zu", n, vector->len);
    return NULL;
  }
  return vector->data[n];
}

void *deleteVectorEl(struct Vector *vector, const size_t n) {
  size_t i;
  void *elToDelete;

  if (n == 0)
    return lPopVectorEl(vector);
  else if (n >= vector->len - 1)
    return rPopVectorEl(vector);

  elToDelete = vector->data[n];
  for (i = n; i < vector->len; ++i)
    vector->data[n] = vector->data[n+1];

  return elToDelete;
}
