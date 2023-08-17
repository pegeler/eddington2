#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "hashmap.h"

#define MAX_LEN 1000
#define DEFAULT_BUCKETS 199

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

  Hashmap *h = h_init(DEFAULT_BUCKETS);
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
      h_ins(h, r);
      if (above > E) above -= h_pop(h, ++E);
    }

    if (c) /* Cumulative print */
      printf("%d\n", E);
  }

  if (!c) /* Summary print if no cumulative */
    printf("%d\n", E);

  return 0;
}
