#ifndef CICADA_VECTOR_H
#define CICADA_VECTOR_H

#include <stddef.h>
#include <stdint.h>

/*
 * The vector data structures described here are largely inspired by C++'s std::vector.
 * A vector is a dynamic array that can be resized when appending elements. Appends are
 * O(1) operations on average. `size` is the number of actual elements stored in the
 * vector while `_cap` is the actual size of the internal array. 

 * Each append checks for the difference between the `size` and `_cap` members. If the
 * difference is +ve, the new elements in simply assiged to the (`size`+1)-th element,
 * and `size` is then incremented.

 * If the difference is 0, realloc is used to resize the internal array and copy existing
 * members to it. The new element to be appended is simply inserted as described above. 
*/


// A vector for integers.
struct IVector {
  size_t size;
  size_t _cap;
  int64_t* data;
};

typedef struct IVector IVector;

// Creates a new IVector and sets `size` & `_cap` to 0.
// `data` is not yet allocated and is set to NULL.
IVector* newIVector();

// Calls free on vector passed after clearing it.
void freeIVector(IVector*);

// Clears vector - frees internal array and resets `_cap` & `size`.
void clearIVector(IVector*);

// Inserts new integer to the back of vector.
void appendToIVector(IVector*, int64_t);

// Creates new int64_t array from vector.
int64_t* newIArrayFromIVector(IVector*);

// Creates new vector from int64_t array.
IVector* newIVectorFromIArray(int64_t*, size_t);

#endif
