#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cstring>

void E(std::istream& input) {
  int running = 0, above = 0;
  double line;
  std::unordered_map<int, int> H(150);

  while(input >> line) {
    int ride = static_cast<int>(line);
    if (ride > running) {
      H[ride]++;
      if (++above > running) {
        running++;
        above -= H[running];
        H.erase(running);
      }
    }
    std::cout << running << std::endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1 || !strcmp(argv[1], "-")) {
    E(std::cin);
  } else {
    std::ifstream file(argv[1]);
    std::istream& file_stream = file;
    E(file_stream);
  }

  return EXIT_SUCCESS;
}
