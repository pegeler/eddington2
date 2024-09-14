#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "vector.h"
#include "read.h"

void usage(char *prog) {
  fprintf(
    stderr,
    "Usage:\n  %s"
    " [-c|--cumulative]"
    " [-h|--help]"
    " [FILE|-]"
    "\n",
    prog
  );
}

/** Compute the eddington number of an integer vector and print the results
 *
 *  @param[in] v the integer vector to compute the Eddington number on
 *  @param[in] c whether to print the cumulative result
 */
void compute_eddington_number(Vector v, int c) {
  int E = 0;
  int *h = calloc(v.size + 1, sizeof(int));

  for (int i=0, above=0; i < v.size; i++) {
    if (v.data[i] > E) {
      if (v.data[i] < v.size) h[v.data[i]]++;
      if (++above > E) above -= h[++E];
    }

    if (c) /* Cumulative print */
      printf("%d\n", E);
  }

  if (!c) /* Summary print if no cumulative */
    printf("%d\n", E);

  free(h);
}

int main(int argc, char *argv[]) {
  Vector v;
  int c, opt;

  c = opt = 0;

  struct option long_options[] = {
    {"help",       no_argument, NULL, 'h'},
    {"cumulative", no_argument, NULL, 'c'},
    {0, 0, 0, 0}
  };

  while ((opt = getopt_long(argc, argv, "ch", long_options, NULL)) != -1)
    switch (opt) {
      case 'c':
        c = 1;
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

  compute_eddington_number(v, c);

  free(v.data);

  return EXIT_SUCCESS;
}
