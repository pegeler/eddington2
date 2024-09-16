/* Quick program for testing out implementations of sorting algorithms */
#include <stdio.h>
#include <stdlib.h>

#include "sort.h"
#include "vector.h"

int main(int argc, char *argv[]) {
  int n = argc - 1;
  int a[n];
  Vector v = {a, n};

  for (int i=0; i < v.size; i++) {
    sscanf(argv[i + 1], "%i", &v.data[i]);
  }

  radix_sort(&v);

  for (int i=0; i < v.size; i++) {
    printf("%i ", v.data[i]);
  }

  putchar('\n');

  return 0;
}
