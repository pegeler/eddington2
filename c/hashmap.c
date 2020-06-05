#include "hashmap.h"

#define BUCKETS 199

static Node *h[BUCKETS];

static unsigned int hash(int key)
{
  return (unsigned int) key % BUCKETS;
}

Node *get(int key)
{
  for (Node *p = h[hash(key)]; p != NULL; p = p->next)
    if (p->key == key)
      return p;
  return NULL;
}

void ins(int key)
{
  Node *p = get(key);
  unsigned int hashval;

  if (p == NULL) {
    p = (Node *) malloc(sizeof(*p));
    hashval = hash(key);
    p->key = key;
    p->val = 1;
    p->next = h[hashval];
    h[hashval] = p;
  } else
    p->val++;
}

int pop(int key)
{
  unsigned int hashval = hash(key);
  Node *prev = NULL;
  int val;

  for (Node *curr = h[hashval]; curr != NULL; curr = curr->next) {
    if (curr->key == key) {
      if (prev == NULL)
        h[hashval] = curr->next;
      else
        prev->next = curr->next;
      val = curr->val;
      free(curr);
      return val;
    }
    prev = curr;
  }

  return 0;
}
