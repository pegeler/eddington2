#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef struct tnode {
  int key;
  int val;
  struct tnode *left;
  struct tnode *right;
} Tnode;

Tnode *get(int key);
void ins(int key);
int pop(int key);

#endif
