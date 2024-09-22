#pragma once

#include <stdlib.h>
#include <limits.h>

#include "vector.h"

/* !!! NOTE: All algorithms sort in-place DESCENDING !!! */

int compare_ints (const void *a, const void *b);
void counting_sort(Vector *v);
void bubble_sort(Vector *v);
void optimized_bubble_sort(Vector *v);
void radix_sort(Vector *v);
void hoares_quick_sort(Vector *v);
void merge_sort(Vector *v);
void insertion_sort(Vector *v);
