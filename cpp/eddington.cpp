#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstring>
#include <unordered_map>


using namespace std;

void usage(char *prog)
{
  cerr << "Usage: " << prog << " [-h] [-cs] FILE" << endl;
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

void E_stream(istream& input, bool const& c) {
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

    if (c) cout << running << endl;

  }
  
  if (!c) cout << running << endl;

}

// Main -----------------------------------------------------------------------

int main(int argc, char *argv[])
{ 

  // Read in commandline args
  bool c = false, s = false;
  int opt;
  
  while ((opt = getopt (argc, argv, "chs")) != -1)
    switch (opt)
      {
      case 'c':
        c = true;
        break;
      case 'h':
        usage(argv[0]);
        return 0;
      case 's':
        s = true;
        break;
      case '?':
        usage(argv[0]);
        return 1;
      }

  // Stream -------------------------------------------------------------------

  if (s)
  { 

    if (optind == argc || !strcmp(argv[optind], "-"))
    {
      E_stream(cin, c);
    }

    else
    {
      ifstream file(argv[optind]);
      istream& file_stream = file;
      E_stream(file_stream, c);
    }

    return 0;

  }


  // Vector -------------------------------------------------------------------

  // Read in ride data
  vector<double> rides;
  
  if (optind == argc || !strcmp(argv[optind], "-"))
  {
    rides = get_rides(cin);
  }

  else
  {
    ifstream file(argv[optind]);
    istream& file_stream = file;
    rides = get_rides(file_stream);
  }

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
