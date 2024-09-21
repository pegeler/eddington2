#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <getopt.h>

#include "EddingtonClass.h"

void usage(char *prog) {
  std::cerr
    << "Usage: "
    << prog
    << " [-h|--help] [-c|--cumulative] [-s|--stream]"
    << " [FILE [FILE...]]"
    << std::endl;
}

std::vector<int> get_rides(std::istream& input) {
  double ride;
  std::vector<int> rides;

  while(input >> ride) {
    rides.push_back(static_cast<int>(ride));
  }

  return rides;
}

int main(int argc, char *argv[]) {
  bool c = false, s = false;
  int opt;

  struct option long_options[] = {

    {"help",       no_argument, NULL, 'h'},
    {"cumulative", no_argument, NULL, 'c'},
    {"stream",     no_argument, NULL, 's'},
    {0, 0, 0, 0}

  };

  while ((opt = getopt_long(argc, argv, "chs", long_options, NULL)) != -1)
    switch (opt) {
      case 'c':
        c = true;
        break;
      case 'h':
        usage(argv[0]);
        return EXIT_SUCCESS;
      case 's':
        s = true;
        break;
      case '?':
        usage(argv[0]);
        return EXIT_FAILURE;
      }

  Eddington e(c);

  if (s) {
    if (optind == argc || !strcmp(argv[optind], "-")) {
      e.update(std::cin);
    } else {
      for (int i = optind; i < argc; i++) {
        std::ifstream file(argv[i]);
        std::istream& file_stream = file;
        e.update(file_stream);
      }
    }
  } else {
    if (optind == argc || !strcmp(argv[optind], "-")) {
      e.update(get_rides(std::cin));
    } else {
      std::vector<int> rides;
      for (int i = optind; i < argc; i++) {
        std::ifstream file(argv[i]);
        std::istream& file_stream = file;
        e.update(get_rides(file_stream));
      }
    }
  }

  if (c)
    for (auto n : *e.getCumulativeEddingtonNumber())
      std::cout << n << std::endl;
  else
    e.print();

  return EXIT_SUCCESS;
}
