#define TEST_NO_MAIN

#include <inttypes.h>

#include "utils.h"
#include "acutest.h"
#include "list/list.h"

#define LEFT               true
#define RIGHT             false
#define SAMPLE_ARR_SIZE       5
#define LOWER_RANGE_LFACTORY -3
#define HIGHER_RANGE_LFACTORY 3

static struct List *listFactory() {
  int32_t i;
  struct List *list = newList();

  for (i = LOWER_RANGE_LFACTORY; i <= HIGHER_RANGE_LFACTORY; ++i)
    rPushListEl(list, newInt32(i));

  return list;
}

static int32_t *arrayFactory() {
  size_t i = 0;
  int32_t *nums = malloc(sizeof(int32_t) * SAMPLE_ARR_SIZE);

  srand(time(NULL));

  for (i = 0; i < SAMPLE_ARR_SIZE; ++i)
    nums[i] = rand();

  return nums;
}

void testNewList(void) {
  struct List *list = newList();

  TEST_ASSERT(list != NULL);

  TEST_CHECK(list->len == 0);
  TEST_CHECK(list->head == NULL);
  TEST_CHECK(list->tail == NULL);

  freeList(list);
}

void testCleanList(void) {
  size_t i;
  struct List *list = newList();

  TEST_ASSERT(list != NULL);

  for (i = 0; i < 10; i++) {
    rPushListEl(list, newInt32(i));
  }

  TEST_CHECK(list->len == 10);
  TEST_CHECK(list->head != NULL);
  TEST_CHECK(list->tail != NULL);

  cleanList(list);

  TEST_CHECK(list->len == 0);
  TEST_CHECK(list->head == NULL);
  TEST_CHECK(list->tail == NULL);

  freeList(list);
}

static void testPopListEl(bool left) {
  char* caseName;
  struct List *list = listFactory();
  size_t totalLen = abs(LOWER_RANGE_LFACTORY) + HIGHER_RANGE_LFACTORY + 1;
  int32_t
    i, *valPtr,
    begin = left ? LOWER_RANGE_LFACTORY : HIGHER_RANGE_LFACTORY,
    end   = left ? HIGHER_RANGE_LFACTORY : LOWER_RANGE_LFACTORY;

  TEST_ASSERT(list != NULL);
  TEST_ASSERT(list->len == 7);

  for (i = begin; i != end + (left ? 1 : -1); i += (left ? 1 : -1)) {
    caseName = int32ToString(i);
    TEST_CASE(caseName);

    valPtr = left ? lPopListEl(list) : rPopListEl(list);

    TEST_CHECK(i == *valPtr);
    TEST_MSG("expected: %" PRId32, i);
    TEST_MSG("produced: %" PRId32, *valPtr);

    TEST_CHECK(list->len == --totalLen);

    free(valPtr);
    free(caseName);
  }

  TEST_CHECK(list->len == 0);

  freeList(list);
}

void testLPopListEl(void) {
  testPopListEl(LEFT);
}

void testRPopListEl(void) {
  testPopListEl(RIGHT);
}

static void testPushListEl(bool left) {
  size_t i;
  char *caseName;
  struct ListNode *node;
  struct List *list = newList();
  int32_t val, *valPtr, *nums = arrayFactory();

  TEST_ASSERT(list != NULL);
  TEST_CHECK(list->len == 0);

  for (i = 0; i < SAMPLE_ARR_SIZE; ++i) {
    valPtr = newInt32(nums[i]);
    TEST_CHECK(left ? lPushListEl(list, valPtr) : rPushListEl(list, valPtr));
  }

  TEST_CHECK(list->len == SAMPLE_ARR_SIZE);

  node = list->head;
  i = left ? SAMPLE_ARR_SIZE - 1 : 0;

  while (node != NULL) {
    caseName = int32ToString(i);
    TEST_CASE(caseName);

    val = *((int32_t*) node->data);
    TEST_CHECK(nums[i] == val);

    TEST_MSG("expected: %" PRId32, nums[i]);
    TEST_MSG("produced: %" PRId32, val);

    i += left ? -1 : 1;
    node = left ? node->next : node->prev;

    free(caseName);
  }

  free(nums);
  freeList(list);
}

void testLPushListEl(void) {
  testPushListEl(LEFT);
}

void testRPushListEl(void) {
  testPushListEl(RIGHT);
}

void testGetListEl(void) {
  size_t i = 0;
  char* caseName;
  struct List *list = newList();
  int32_t val, *nums = arrayFactory();

  TEST_ASSERT(list != NULL);
  TEST_CHECK(list->len == 0);

  for (i = 0; i < SAMPLE_ARR_SIZE; ++i)
    rPushListEl(list, newInt32(nums[i]));

  TEST_CHECK(list->len == SAMPLE_ARR_SIZE);

  for (i = 0; i < SAMPLE_ARR_SIZE; ++i) {
    caseName = int32ToString(i);
    TEST_CASE(caseName);

    val = *((int32_t*) getListEl(list, i));
    TEST_CHECK(nums[i] == val);

    TEST_MSG("expected: %" PRId32, nums[i]);
    TEST_MSG("produced: %" PRId32, val);

    free(caseName);
  }

  free(nums);
  freeList(list);
}

void testDeleteListEl(void) {
  struct List *list = listFactory();

  TEST_ASSERT(list != NULL);

  freeList(list);
}
