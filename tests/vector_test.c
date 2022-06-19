#define TEST_NO_MAIN

#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>

#include "utils.h"
#include "acutest.h"
#include "vector/vector.h"

#define LEFT                 true
#define RIGHT                false
#define UPPER_RANGE_VFACTORY 10
#define LOWER_RANGE_VFACTORY -UPPER_RANGE_VFACTORY
#define V_FACTORY_LEN        UPPER_RANGE_VFACTORY * 2 + 1

static struct Vector *vectorFactory() {
  int32_t i;
  struct Vector *vector = newVectorReserved(V_FACTORY_LEN);

  for (i = LOWER_RANGE_VFACTORY; i <= UPPER_RANGE_VFACTORY; ++i)
    rPushVectorEl(vector, newInt32(i));

  return vector;
}

static int32_t *arrayFactory() {
  size_t idx = 0;
  int32_t val, *nums = malloc(sizeof(int32_t) * V_FACTORY_LEN);

  for (val = LOWER_RANGE_VFACTORY; val <= UPPER_RANGE_VFACTORY; ++val)
    nums[idx++] = val;

  return nums;
}

static int32_t getInt32FromVector(struct Vector *vector, const size_t idx) {
  assert(idx < vector->len);
  return *((int32_t*) vector->data[idx]);
}

void testNewVector(void) {
  struct Vector *vector = newVector();

  TEST_ASSERT(vector != NULL);

  TEST_CHECK(vector->len == 0);
  TEST_CHECK(vector->cap == 2);
  TEST_CHECK(vector->data != NULL);

  freeVector(vector);
}

static void testPushVectorEl(bool left) {
  char *caseName;
  int32_t  *valPtr;
  size_t i, oldCapacity;
  bool checkCapacityGrowth = false;
  struct Vector *vector = newVector();
  bool (*pushVectorElFunc)(struct Vector*, void*) = left ? lPushVectorEl : rPushVectorEl;

  TEST_ASSERT(vector != NULL);
  TEST_CHECK(vector->len == 0);

  srand(time(NULL));

  for (i = 0; i < 10; ++i) {
    valPtr = newInt32(rand());
    caseName = int32ToString(i+1);

    TEST_CASE(caseName);
    TEST_CHECK(pushVectorElFunc(vector, valPtr));

    TEST_CHECK(vector->len = i+1);

    TEST_CHECK(getInt32FromVector(vector, left ? 0 : i) == *valPtr);

    if (checkCapacityGrowth)
      TEST_CHECK(vector->cap == oldCapacity * 2);

    oldCapacity = vector->cap;
    checkCapacityGrowth = vector->len == vector->cap;

    free(caseName);
  }

  freeVector(vector);
}

void testLPushVectorEl(void) {
  testPushVectorEl(LEFT);
}

void testRPushVectorEl(void) {
  testPushVectorEl(RIGHT);
}

void testPopVectorEl(bool left) {
  char *caseName;
  struct Vector *vector = vectorFactory();
  int32_t i, begin, end, *valPtr, *nums = arrayFactory();
  void* (*popVectorElFunc) (struct Vector*) = left ? lPopVectorEl : rPopVectorEl;

  TEST_ASSERT(nums != NULL);
  TEST_ASSERT(vector != NULL);

  begin = left ? 0 : (V_FACTORY_LEN - 1);
  end   = left ? V_FACTORY_LEN : -1;

  for (i = begin; i != end; i += left ? 1 : -1) {
    caseName = int32ToString(i);

    TEST_CASE(caseName);

    valPtr = (int32_t*) popVectorElFunc(vector);

    TEST_CHECK(nums[i] == *valPtr);

    TEST_MSG("expected: %" PRId32, nums[i]);
    TEST_MSG("produced: %" PRId32, *valPtr);

    free(valPtr);
    free(caseName);
  }

  free(nums);
  freeVector(vector);
}

void testLPopVectorEl(void) {
  testPopVectorEl(LEFT);
}

void testRPopVectorEl(void) {
  testPopVectorEl(RIGHT);
}

void testDeleteVectorEl(void) {
}

void testSetVectorEl(void) {
  int32_t* nums = arrayFactory();
  struct Vector *vector = newVector();
}
