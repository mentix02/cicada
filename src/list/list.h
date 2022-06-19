#ifndef CICADA_LIST_H
#define CICADA_LIST_H

#include <stddef.h>
#include <stdbool.h>

struct ListNode {
  void *data;
  struct ListNode *next;
  struct ListNode *prev;
};

struct List {
  size_t len;
  struct ListNode *head;
  struct ListNode *tail;
};

struct List *newList();

void freeList(struct List*);  // O(n)
void cleanList(struct List*); // O(n)

void *lPopListEl(struct List*); // O(1)
void *rPopListEl(struct List*); // O(1)

bool lPushListEl(struct List*, void*); // O(1)
bool rPushListEl(struct List*, void*); // O(1)

void *getListEl(struct List*, size_t); // O(k)

void *deleteListEl(struct List*, size_t);       // O(k)
bool setListEl(struct List*, size_t, void*);    // O(k)
bool insertListEl(struct List*, size_t, void*); // O(k)

#endif // CICADA_LIST_H
