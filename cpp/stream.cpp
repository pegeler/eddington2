#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cstring>

using namespace std;

void E(istream& input) {
  int ride, running = 0, above = 0;
  double line;
  unordered_map<int, int> H;

  while(input >> line)
  {
    ride = (int) line;
    
    if (ride > running) {
      above++;
      H[ride]++;

      if (above > running) {
        running++;
        above -= H[running];
      }
    }

    cout << running << endl;

  }

}

int main(int argc, char *argv[])
{ 

  if (argc == 1 || !strcmp(argv[1], "-"))
  {
    E(cin);
  }

  else
  {
    ifstream file(argv[1]);
    istream& file_stream = file;
    E(file_stream);
  }

  return 0;

}
