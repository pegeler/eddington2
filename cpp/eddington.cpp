#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstring>
#include <unordered_map>
#include <getopt.h>


using namespace std;

void usage(char *prog)
{
  cerr
    << "Usage: "
    << prog
    << " [-h|--help] [-c|--cumulative] [-s|--stream]"
    << " [FILE [FILE...]]"
    << endl;
}

// Vector-based solution -----------------------------------------------------

vector<double> get_rides(istream& input)
{
  double ride;
  vector<double> rides;

  while(input >> ride)
  {
    rides.push_back(ride);
  }

  return rides;

}

int E_num(vector<double> &rides) {
  int n = rides.size(), E = 0, ride = 0, above = 0;
  vector<int> H(n, 0);

  for ( int i = 0; i < n; i++ ) {
    ride = (int) rides[i];
    if (ride > E) {
      above++;
      if (ride < n) H[ride]++;

      if (above > E) {
        E++;
        above -= H[E];
      }
    }
  }

  return E;

}

vector<int> E_cum(vector<double> &rides) {
  int n = rides.size(), running = 0, ride = 0, above = 0;
  vector<int> E(n, 0), H(n, 0);

  for ( int i = 0; i < n; i++ ) {
    ride = (int) rides[i];
    if (ride > running) {
      above++;
      if (ride < n) H[ride]++;

      if (above > running) {
        running++;
        above -= H[running];
      }
    }

    E[i] = running;

  }

  return E;

}

// Stream-based solution ------------------------------------------------------

class Eddington {
  private:

    int above=0;
    int running=0;
    unordered_map<int, int> H = unordered_map<int, int>(150);

  public:

  void update(istream& input, bool const& c) {
    int ride;
    double line;

    while(input >> line)
    {
      ride = (int) line;

      if (ride > running) {
        above++;
        H[ride]++;

        if (above > running) {
          running++;
          above -= H[running];
          H.erase(running);
        }
      }

      if (c) cout << running << endl;

    }

  }

  void print(void) {
    cout << running << endl;
  }

};

// Main -----------------------------------------------------------------------

int main(int argc, char *argv[])
{

  // Read in commandline args
  int c = 0, s = 0;
  int opt;

  struct option long_options[] = {

    {"help",       no_argument, NULL, 'h'},
    {"cumulative", no_argument, NULL, 'c'},
    {"stream",     no_argument, NULL, 's'},
    {0, 0, 0, 0}

  };

  while ((opt = getopt_long(argc, argv, "chs", long_options, NULL)) != -1)
    switch (opt)
      {
      case 'c':
        c = 1;
        break;
      case 'h':
        usage(argv[0]);
        return 0;
      case 's':
        s = 1;
        break;
      case '?':
        usage(argv[0]);
        return 1;
      }

  // Stream -------------------------------------------------------------------

  if (s)
  {
    Eddington e;

    if (optind == argc || !strcmp(argv[optind], "-")) {
      e.update(cin, c);
    }

    else {
      for ( int i = optind; i < argc; i++ ) {
        ifstream file(argv[i]);
        istream& file_stream = file;
        e.update(file_stream, c);
      }
    }

    if (!c) e.print();

    return 0;

  }


  // Vector -------------------------------------------------------------------

  // Read in ride data
  vector<double> rides;

  if (optind == argc || !strcmp(argv[optind], "-")) {
    rides = get_rides(cin);
  }

  else {
    for ( int i = optind; i < argc; i++ ) {
      ifstream file(argv[i]);
      istream& file_stream = file;
      vector<double> tmp = get_rides(file_stream);
      rides.insert(rides.end(), tmp.begin(), tmp.end());
    }
  }

  // Caluclate E_num and print
  if (!c) {
    cout << E_num(rides) << endl;
  }

  // Else print E_cum
  else {
    auto E = E_cum(rides);

    for ( auto const &i : E ) {
      cout << i << endl;
    }
  }

  return 0;

}
