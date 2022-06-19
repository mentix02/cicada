#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static struct ListNode *newNode(void *data) {
  struct ListNode *n = malloc(sizeof(struct ListNode));

  if (n == NULL)
    return NULL;

  n->data = data;
  n->next = NULL;
  n->prev = NULL;

  return n;
}

static void freeNode(struct ListNode *n) {
  free(n->data);
  free(n);
}

struct List *newList() {
  struct List *l = malloc(sizeof(struct List));

  if (l == NULL)
    return NULL;

  l->len = 0;
  l->head = NULL;
  l->tail = NULL;

  return l;
}

void freeList(struct List *l) {
  cleanList(l);
  free(l);
}

void cleanList(struct List *l) {
  struct ListNode *curr, *temp;

  if (l == NULL) return;

  curr = l->head;

  while (curr != NULL) {
    temp = curr->next;
    freeNode(curr);
    curr = temp;
  }

  l->head = NULL;
  l->tail = NULL;
  l->len = 0;
}

static void *popListEl(struct List *l, bool left) {
  void *dataToReturn;
  struct ListNode *oldNode;
  const size_t len = l->len;

  assert(len > 0);

  oldNode = left ? l->head : l->tail;
  dataToReturn = oldNode->data;

  if (len == 1) {
    free(oldNode);
    l->head = l->tail = NULL;
    l->len = 0;
    return dataToReturn;
  }

  if (left) {
    l->head = oldNode->next;
    l->head->prev = NULL;
  } else {
    l->tail = oldNode->prev;
    l->tail->next = NULL;
  }

  // Cannot call freeNode here since
  // we need to return the void* data
  // pointer and freeNode would've
  // freed that memory as well.
  free(oldNode);
  l->len--;

  return dataToReturn;
}

void *lPopListEl(struct List *l) {
  return popListEl(l, true);
}

void *rPopListEl(struct List *l) {
  return popListEl(l, false);
}

static bool pushListEl(struct List *l, void *data, bool left) {
  const size_t len = l->len;
  struct ListNode *n = newNode(data);

  if (n == NULL)
    return false;

  if (len == 0) {
    l->head = l->tail = n;
    l->len = 1;
    return true;
  }

  if (left) {
    l->head->prev = n;
    n->next = l->head;
    l->head = n;
  } else {
    l->tail->next = n;
    n->prev = l->tail;
    l->tail = n;
  }

  l->len++;
  return true;
}

bool lPushListEl(struct List *l, void *data) {
  return pushListEl(l, data, true);
}

bool rPushListEl(struct List *l, void *data) {
  return pushListEl(l, data, false);
}

void *getListEl(struct List *l, size_t idx) {
  struct ListNode *node = l->head;

  if (idx >= l->len) {
    printf("warning: tried el #%zu from List size %zu\n", idx, l->len);
    return NULL;
  }

  while (idx-- > 0)
    node = node->next;

  return node->data;
}

void *deleteListEl(struct List *l, size_t idx) {
  void *dataToReturn;
  struct ListNode *nodeToBeDeleted;

  if (idx >= l->len) {
    printf("warning: tried el #%zu from List size %zu\n", idx, l->len);
    return NULL;
  }

  if (idx == 0)
    return lPopListEl(l);
  else if (idx == l->len - 1)
    return rPopListEl(l);
  else {
    nodeToBeDeleted = l->head;

    while (idx-- > 0)
      nodeToBeDeleted = nodeToBeDeleted->next;

    dataToReturn = nodeToBeDeleted->data;
    nodeToBeDeleted->prev->next = nodeToBeDeleted->next;
    nodeToBeDeleted->next->prev = nodeToBeDeleted->prev;

    l->len--;

    free(nodeToBeDeleted);
    return dataToReturn;
  }
}

bool setListEl(struct List *l, size_t idx, void *data) {
  struct ListNode *node;

  if (idx >= l->len) {
    printf("warning: tried el #%zu from List size %zu\n", idx, l->len);
    return false;
  }

  node = l->head;

  while (idx-- > 0)
    node = node->next;

  node->data = data;
  return true;
}

bool insertListEl(struct List *l, size_t idx, void *data) {
  struct ListNode *nextNode, *previousNode, *nodeToBeInserted = newNode(data);

  if (idx == 0)
    return lPushListEl(l, data);
  else if (idx >= l->len)
    return rPushListEl(l, data);
  else {
    previousNode = l->head;

    while (idx-- > 1)
      previousNode = previousNode->next;

    nextNode = previousNode->next;
    previousNode->next = nodeToBeInserted;
    nodeToBeInserted->prev = previousNode;

    nodeToBeInserted->next = nextNode;
    nextNode->prev = nodeToBeInserted;

    l->len++;
    return true;
  }
}
