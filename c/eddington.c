#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

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

/** Read lines from file stream and return them as an integer array
 *
 *  @param[in] file the file stream to read from
 *  @param[out] n will be written with the number of values read in
 */
int *read_values(FILE *file, int *n) {
  char line[MAX_LEN];
  int len = 1024;
  int *r = malloc(len * sizeof(int));
  while (fgets(line, MAX_LEN, file) != NULL) {
    if (*n >= len) {
      len *= 2;
      r = realloc(r, len * sizeof(int));
    }
    r[(*n)++] = atoi(line);
  }
  return r;
}

/** Compute the eddington number of an integer array and print the results
 *
 *  @param[in] r the integer array to compute the Eddington number on
 *  @param[in] n the length of \p r
 *  @param[in] c whether to print the cumulative result
 */
void compute_eddington_number(int *r, int n, int c) {
  int *h = calloc(n + 1, sizeof(int));

  int E = 0;
  for (int i=0, above=0; i < n; i++) {
    if (r[i] > E) {
      if (r[i] < n) h[r[i]]++;
      if (++above > E) above -= h[++E];
    }

    if (c) /* Cumulative print */
      printf("%d\n", E);
  }

  if (!c) /* Summary print if no cumulative */
    printf("%d\n", E);
}

int main(int argc, char *argv[]) {
  int *r;
  int n, c, opt;

  n = c = opt = 0;

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
    r = read_values(file, &n);
    fclose(file);
  } else {
    r = read_values(stdin, &n);
  }

  compute_eddington_number(r, n, c);

  return EXIT_SUCCESS;
}
