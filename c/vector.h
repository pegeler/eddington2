#pragma once

typedef struct {
  int *data;
  int size;
} Vector;

void v_cleanup(Vector v);
