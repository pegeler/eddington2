#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

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

  if (argc != 2) {
    cerr << argv[0] << ": Invalid number of arguments." << endl 
         << "Usage: E_num FILE" << endl
         << "  or:  E_cum FILE" << endl; 
    return 1;
  }

  auto rides = get_rides(argv[1]);

  // E_num 
  if (!strcmp(argv[0],"E_num"))
  {
    cout << E_num(rides) << endl;
  }

  // E_cum
  else if (!strcmp(argv[0],"E_cum"))
  {
    auto E = E_cum(rides);

    for ( auto const &i : E ) {
      cout << i << endl;
    }
  }

  else {
    cerr << argv[0] << ": Command not recognized." << endl;
    return 1;
  }

  return 0;

}
