#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "vector.h"

Vector read_values(FILE *file) {
  int len = 1024;
  Vector v = {
    malloc(len * sizeof(int)),
    0
  };
  char line[MAX_LEN];
  while (fgets(line, MAX_LEN, file) != NULL) {
    if (v.size >= len) {
      len *= 2;
      if ((v.data = realloc(v.data, len * sizeof(int))) == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
      }
    }
    v.data[v.size++] = atoi(line);
  }
  return v;
}
