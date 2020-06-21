#include "hashmap.h"

static uint32 hash(uint32 buckets, uint32 key)
{
  return key % buckets;
}

Hashmap *h_init(uint32 size)
{
  Hashmap *h = (Hashmap *) malloc(sizeof(Hashmap));
  size = size * 1.33f;
  if (size < 17)
    h->buckets = 17;
  else
    h->buckets = is_prime(size) ? size : next_prime(size);

  h->size = 0;
  h->nodes = calloc(h->buckets, sizeof(Node *));

  return h;
}

Node *h_get(Hashmap *h, uint32 key)
{
  for (Node *p = h->nodes[hash(h->buckets, key)]; p != NULL; p = p->next)
    if (p->key == key)
      return p;
  return NULL;
}

uint32 h_pop(Hashmap *h, uint32 key)
{
  uint32 hashval = hash(h->buckets, key);
  uint32 val;
  Node *prev = NULL;

  for (Node *curr = h->nodes[hashval]; curr != NULL; curr = curr->next) {
    if (curr->key == key) {
      if (prev == NULL)
        h->nodes[hashval] = curr->next;
      else
        prev->next = curr->next;
      val = curr->val;
      free(curr);
      h->size--;
      h_resize(h);
      return val;
    }
    prev = curr;
  }
  return 0;
}

void h_ins(Hashmap *h, uint32 key)
{
  Node *p = h_get(h, key);
  uint32 hashval;

  if (p == NULL) {
    h->size++;
    h_resize(h);

    p = (Node *) malloc(sizeof(Node));
    if (p == NULL) {
      fprintf(stderr, "Could not allocate node in hashmap\n");
      exit(1);
    }

    hashval = hash(h->buckets, key);
    p->key = key;
    p->val = 1;
    p->next = h->nodes[hashval];
    h->nodes[hashval] = p;
  } else {
    p->val++;
  }
}

uint32 h_resize(Hashmap *h) {
  /* Test if resize is necessary */
  uint32 old_buckets = h->buckets;

  if (h->size < 12 && h->buckets != 17) {
    h->buckets = 17;
  } else if (h->size > h->buckets * 0.75f) {
    h->buckets = next_prime(h->buckets * 2);
  } else if (h->size * 4 < h->buckets) {
    h->buckets = next_prime(h->size * 2);
  } else {
    return 0;
  }

  /* If yes, do resize */
  uint32 hashval;
  Node **tmp = h->nodes;
  Node *p, *q;
  h->nodes = calloc(h->buckets, sizeof(Node *));
  for (int i=0; i < old_buckets; i++) {
    p = tmp[i];
    while (p != NULL) {
      hashval = hash(h->buckets, p->key);
      q = p->next;
      p->next = h->nodes[hashval];
      h->nodes[hashval] = p;
      p = q;
    }
  }

  free(tmp);
  return h->buckets;
}
