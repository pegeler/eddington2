#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

typedef struct node {
  int key;
  int val;
  struct node *next;
} Node;

Node *get(int key);
void ins(int key);
int pop(int key);

#endif
