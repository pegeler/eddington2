#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "tree.h"

#define MAX_LEN 1000

void usage(char *prog) {
  fprintf(
    stderr,
    "Usage:\n  %s"
    " [-c|--cumulative]"
    " [-h|--help]"
    /* " [FILE [FILE...]]" TODO */
    "\n",
    prog
  );
}

int main(int argc, char *argv[])
{

  char line[MAX_LEN];
  int E, above, r, c, opt;
  E = above = r = c = opt = 0;

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


  while (fgets(line, MAX_LEN, stdin) != NULL) {
    r = atoi(line);
    if (r > E) {
      above++;
      ins(r);
      if (above > E) above -= pop(++E);
    }

    if (c) /* Cumulative print */
      printf("%d\n", E);
  }

  if (!c) /* Summary print if no cumulative */
    printf("%d\n", E);

  return 0;
}
