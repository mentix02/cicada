#ifndef CICADA_VECTOR_H
#define CICADA_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

/*
 * Vector is a generic dynamic array with no
 * fixed length as is the case with static arrays.
 * It can grow (and sometimes shrink) on an as
 * need basis. Mostly complies with a similar API
 * as List or any other "linear" data structure.
 */

struct Vector {
  size_t len;
  size_t cap;
  void** data;
};

struct Vector *newVector();               // O(1)
struct Vector *newVectorReserved(size_t); // O(1)

void freeVector(struct Vector*);  // O(n)
void cleanVector(struct Vector*); // O(n)

void *lPopVectorEl(struct Vector*); // O(n)
void *rPopVectorEl(struct Vector*); // O(1)

bool lPushVectorEl(struct Vector*, void*); // O(n)
bool rPushVectorEl(struct Vector*, void*); // O(1) avg

void *getVectorEl(struct Vector*, size_t);          // O(1)
bool setVectorEl(struct Vector*, size_t, void*);    // O(1)
void *deleteVectorEl(struct Vector*, size_t);       // O(n)
bool insertVectorEl(struct Vector*, size_t, void*); // O(n)

#endif
