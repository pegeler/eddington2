#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

void usage(char *prog)
{
  cerr << "Usage: " << prog << " [-c] FILE" << endl;
}

vector<double> get_rides(string filename)
{
  double ride;
  ifstream file(filename);

  vector<double> rides;

  while(file >> ride)
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

int main(int argc, char *argv[])
{ 

  // Read in commandline args
  bool c = false;
  int opt;
  
  while ((opt = getopt (argc, argv, "c")) != -1)
    switch (opt)
      {
      case 'c':
         c = true;
        break;
      case '?':
        usage(argv[0]);
        return 1;
      }

  if (optind == argc)
  {
    cerr << argv[0] << ": no file specified." << endl;
    usage(argv[0]);
    return 1;
  }

  // Read in ride data
  auto rides = get_rides(argv[optind]);

  // Caluclate E_num and print
  if (!c)
  {
    cout << E_num(rides) << endl;
  }

  // Else print E_cum
  else 
  {
    auto E = E_cum(rides);

    for ( auto const &i : E ) {
      cout << i << endl;
    }
  }

  return 0;

}
