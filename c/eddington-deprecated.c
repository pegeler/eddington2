#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "sort.h"
#include "read.h"

void usage(char *prog) {
  fprintf(
    stderr,
    "Usage:\n  %s"
    " [-s METHOD|--sort-method METHOD]"
    " [-h|--help]"
    " [FILE|-]"
    "\n\n"
    "  Where METHOD is...\n"
    "    0: counting sort (default)\n"
    "    1: stdlib's qsort\n"
    "    2: bubble sort\n"
    "    3: optimized bubble sort\n"
    "    4: radix sort\n"
    "    5: Hoare's quick sort\n"
    "    6: Merge sort\n"
    "    7: Insertion sort\n",
    prog
  );
}

int compute_eddington_number(const Vector v) {
  int E = 0;
  for (; E < v.size; E++) {
    if (v.data[E] < E + 1) break;
  }
  return E;
}

int main(int argc, char *argv[]) {
  Vector v;
  int s, opt;

  s = opt = 0;

  struct option long_options[] = {
    {"help",       no_argument, NULL, 'h'},
    {"sort-method", required_argument, NULL, 's'},
    {0, 0, 0, 0}
  };

  while ((opt = getopt_long(argc, argv, "hs:", long_options, NULL)) != -1)
    switch (opt) {
      case 's':
        s = atoi(optarg);
        break;
      case 'h':
        usage(argv[0]);
        return EXIT_SUCCESS;
      case '?':
        usage(argv[0]);
        return EXIT_FAILURE;
    }

  if (optind < argc && strncmp(argv[optind], "-", 1)) {
    FILE *file;
    if ((file = fopen(argv[optind], "r")) == NULL) {
      fprintf(stderr, "Could not open file %s\n", argv[optind]);
      return EXIT_FAILURE;
    }
    v = read_values(file);
    fclose(file);
  } else {
    v = read_values(stdin);
  }

  switch (s) {
    case 0:
      counting_sort(&v);
      break;
    case 1:
      qsort(v.data, v.size, sizeof(int), compare_ints);
      break;
    case 2:
      bubble_sort(&v);
      break;
    case 3:
      optimized_bubble_sort(&v);
      break;
    case 4:
      radix_sort(&v);
      break;
    case 5:
      hoares_quick_sort(&v);
      break;
    case 6:
      merge_sort(&v);
      break;
    case 7:
      insertion_sort(&v);
      break;
    default:
      usage(argv[0]);
      return EXIT_FAILURE;
    // TODO: More sorting algorithms
  }

  printf("%d\n", compute_eddington_number(v));

  v_cleanup(v);

  return EXIT_SUCCESS;
}
