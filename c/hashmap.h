#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include "primes.h"

typedef struct node {
  uint32 key;
  uint32 val;
  struct node *next;
} Node;

typedef struct hashmap {
  Node **nodes;
  uint32 buckets;
  uint32 size;
} Hashmap;

Hashmap *h_init(uint32 size);
Node  *h_get(Hashmap *h,  uint32 key);
void   h_ins(Hashmap *h,  uint32 key);
uint32 h_pop(Hashmap *h,  uint32 key);
uint32 h_resize(Hashmap *h);

#endif
