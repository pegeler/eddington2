#include <vector>

#include "EddingtonClass.h"

Eddington::Eddington() {}

Eddington::Eddington(bool store_cumulative) {
  if (store_cumulative) {
    m_cumulative = std::vector<int>();
  }
}

Eddington::Eddington(const std::vector<int> &rides, bool store_cumulative)
    : Eddington::Eddington(store_cumulative) {
  update(rides);
}

int Eddington::getNumberToNext() { return m_eddington_number + 1 - m_n_above; }

int Eddington::getNumberToTarget(int target) {
  if (target == m_eddington_number + 1) {
    // Early exit for trivial case.
    return getNumberToNext();
  }

  int completed_rides = 0;
  for (auto it = m_hashmap.begin(); it != m_hashmap.end(); ++it)
    if (it->first >= target)
      completed_rides += it->second;
  return target - completed_rides;
}

void Eddington::update(int ride) {
  if (ride > m_eddington_number) {
    m_n_above++;
    m_hashmap[ride]++;
    if (m_n_above > m_eddington_number) {
      m_n_above -= m_hashmap[++m_eddington_number];
      m_hashmap.erase(m_eddington_number);
    }
  }
  if (m_cumulative) {
    m_cumulative->push_back(m_eddington_number);
  }
}

void Eddington::update(const std::vector<int> &rides) {
  for (auto ride : rides) update(ride);
}


void Eddington::update(std::istream& rides) {
  double line;
  while(rides >> line) update(static_cast<int>(line));
}

void Eddington::print() {
  std::cout << m_eddington_number << std::endl;
}
