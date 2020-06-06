#include "tree.h"

static Tnode *tree;

Tnode *get(int key)
{
  Tnode *node = tree;
  while (node != NULL) {
    if (node->key > key)
      node = node->left;
    else if (node->key < key)
      node = node->right;
    else
      return node;
  }
  return NULL;
}

void ins(int key)
{
  if (tree == NULL) {
    tree = (Tnode *) malloc(sizeof(*tree));
    tree->key = key;
    tree->val = 1;
    return;
  }

  for (Tnode *node = tree;;) {
    if (node->key > key) {
      if (node->left != NULL)
        node = node->left;
      else {
        node->left = (Tnode *) malloc(sizeof(*node));
        node = node->left;
        node->key = key;
        node->val = 1;
        return;
      }
    } else if (node->key < key) {
      if (node->right != NULL)
        node = node->right;
      else {
        node->right = (Tnode *) malloc(sizeof(*node));
        node = node->right;
        node->key = key;
        node->val = 1;
        return;
      }
    } else {
      node->val++;
      return;
    }
  }
}

int pop(int key)
{
  // TODO Actually remove unused node!
  Tnode *node = get(key);
  return node == NULL ? 0 : node->val;
}
