#define TEST_NO_MAIN

#include "acutest.h"
#include "a/array.h"
#include "ds/list.h"

void test_newIList(void) {
  IList* list = newIList();

  TEST_ASSERT(list != NULL);

  freeIList(list);
}

void test_clearIList(void) {
  IList* list = newIList();
  appendToIList(list, 31);
  appendToIList(list, 98);

  TEST_CHECK(list->size == 2);
  TEST_CHECK(list->head != NULL);

  clearIList(list);

  TEST_CHECK(list->size == 0);
  TEST_CHECK(list->head == NULL);
  TEST_CHECK(list->tail == NULL);

  freeIList(list);
}

void test_newIArrayFromIList(void) {
  int64_t orig_arr[5] = {2, 3, 1, 6, 4};
  IList* list = newIList();

  TEST_ASSERT(list != NULL);

  for (size_t i = 0; i < 5; ++i)
    appendToIList(list, orig_arr[i]);

  int64_t* list_arr = newIArrayFromIList(list);

  TEST_ASSERT(list_arr != NULL);

  TEST_CHECK(i64ArrayCmp(orig_arr, 5, list_arr, 5));

  free(list_arr);
  freeIList(list);
}

void test_appendToIList(void) {
  size_t i;
  IList* list = newIList();
  int64_t arr[3] = {32, 83, 76};

  TEST_ASSERT(list != NULL);

  for (i = 0; i < 3; ++i)
    appendToIList(list, arr[i]);

  i = 0;
  IListNode* currNode = list->head;
  while (currNode != NULL) {
    TEST_CHECK(arr[i++] == currNode->data);
    currNode = currNode->next;
  }

  freeIList(list);
}
