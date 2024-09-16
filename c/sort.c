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

static void validate_input(Vector *v) {
  if (min_element(v) < 0)
    error(1, 0, "All elements must be integers >= 0");
}

void counting_sort(Vector *v) {
  validate_input(v);
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


static void rs(int *a, int n, int digit) {
  if (digit < 0) return;

  int lo = 0, hi = n;
  int mask = 1 << digit--;
  while (lo < hi) {
    if (!(a[lo] & mask)) {
      swap(a + lo, a + --hi);
    } else {
      lo++;
    }
  }

  if (lo) rs(a, lo, digit);
  if (hi < n) rs(a + hi, n - hi, digit);
}

void radix_sort(Vector *v) {
  validate_input(v);
  rs(v->data, v->size, (sizeof(int) - 1) * 8);
}


static void hqs(int *a, int n) {
  if (n < 2) return;
  int pivot;
  error(1, 0, "Algorithm not implemented yet!");
  /* TODO */
}

void hoares_quick_sort(Vector *v) {
  hqs(v->data, v->size);
}

void merge_sort(Vector *v) {
  /* TODO */
  error(1, 0, "Algorithm not implemented yet!");
}

void insertion_sort(Vector *v) {
  /* TODO */
  error(1, 0, "Algorithm not implemented yet!");
}