#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define MAX_LEN 1000

void usage(char *prog) {
  fprintf(
    stderr,
    "Usage:\n  %s"
    " [-c|--cumulative]"
    " [-h|--help]"
    //" [FILE [FILE...]]" TODO
    "\n",
    prog
  );
}

int main(int argc, char *argv[])
{

  char line[MAX_LEN];
  int len = 10;
  int n, c, opt;
  int *r = calloc(len, sizeof(int));

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
        return 0;
      case '?':
        usage(argv[0]);
        return 1;
    }

  // Read in file
  for (; fgets(line, MAX_LEN, stdin) != NULL; n++) {
    if (n >= len) {
      len *= 2;
      r = realloc(r, len * sizeof(int));
    }
    r[n] = (int) atof(line);
  }

  r = realloc(r, n * sizeof(int));

  // Initialize histogram
  int *h = calloc(n, sizeof(int));
  for (int i=0; i < n; i++)
    h[i] = 0;

  // Run the algorithm
  int E = 0;
  for (int i=0, above=0; i < n; i++) {
    if (r[i] > E) {
      above++;
      if (r[i] < n) {
        h[r[i]]++;
      }
      if (above > E) {
        E++;
        above -= h[E];
       }
    }
    // Cumulative print
    if (c)
      printf("%d\n", E);
  }

  // Summary print if no cumulative
  if (!c)
    printf("%d\n", E);

  return 0;
}
