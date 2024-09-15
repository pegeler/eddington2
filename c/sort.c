#include <stdlib.h>
#include <limits.h>
#include <error.h>

#include "vector.h"

static void swap(int *a, int *b) {
    int tmp;
    tmp = *a, *a = *b, *b = tmp;
}

static int max_element(Vector *v) {
  int best=INT_MIN;
  for (int i=0; i < v->size; i++)
    if (v->data[i] > best)
      best = v->data[i];
  return best;
}

static int min_element(Vector *v) {
  int best=INT_MAX;
  for (int i=0; i < v->size; i++)
    if (v->data[i] < best)
      best = v->data[i];
  return best;
}

int compare_ints (const void *a, const void *b) {
  return *(int*)b - *(int*)a;
}

void counting_sort(Vector *v) {
  if (min_element(v) < 0)
    error(1, 0, "All elements must be integers >= 0");
  volatile int max = max_element(v);
  int *a = (int *) calloc((unsigned int) max + 1, sizeof(int));

  if (a == NULL)
    error(1, 0, "Could not allocate memory");

  /* make an array of counts */
  for (int i=0; i < v->size; i++)
    a[*(v->data + i)]++;

  /* replace existing array with reverse-sorted data */
  for (int i=0; max >= 0; max--)
    while (a[max]--)
      v->data[i++] = max;

  free(a);
}

void bubble_sort(Vector *v) {
  for (;;) {
    int swapped = 0;
    for (int i=1; i < v->size; i++) {
      if (v->data[i - 1] < v->data[i]) {  /* Descending */
        swapped = 1;
        swap(v->data + i, v->data + i - 1);
      }
    }
    if (!swapped) return;
  }
}

void optimized_bubble_sort(Vector *v) {
  int n = v->size;
  while (n > 1) {
    int swapped = 0;
    int i = 1, j = 1;
    for (; i < n; i++) {
      if (v->data[i - 1] < v->data[i]) {  /* Descending */
        swapped = 1;
        j = i;
        swap(v->data + i, v->data + i - 1);
      }
    }
    if (!swapped) return;
    n = j;
  }
}

void quick_sort(Vector *v) {
  /* TODO */
}

void merge_sort(Vector *v) {
  /* TODO */
}

void insertion_sort(Vector *v) {
  /* TODO */
}
