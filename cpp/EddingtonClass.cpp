#include "EddingtonClass.h"

int Eddington::E() {
  return running;
}

std::vector<int> Eddington::E_vec() {
  return cumulative;
}

void Eddington::update(std::istream& input, bool const verbose) {
  int ride;
  double line;

  while( input >> line )
  {
    ride = (int) line;

    if ( ride > running ) {
      above++;
      H[ride]++;

      if ( above > running ) {
        running++;
        above -= H[running];
        H.erase(running);
      }
    }

    if (verbose) print();
    cumulative.push_back(running);

  }

}

void Eddington::print() {
  std::cout << running << std::endl;
}

int Eddington::next() {
  return running + 1 - above;
}

int Eddington::required(int target) {
  if ( running > target ) return 0;
  if ( target == running + 1 ) return this->next();

  int sum=0;

  for ( auto it = H.begin(); it != H.end(); ++it ) {
    if ( it->first >= target ) sum += it->second;
  }

  return target - sum;

}
