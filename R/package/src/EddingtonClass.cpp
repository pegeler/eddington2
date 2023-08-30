#include "EddingtonClass.h"

#include <Rcpp.h>
#include <optional>
#include <vector>

Eddington::Eddington() {}

Eddington::Eddington(bool store_cumulative) {
  if (store_cumulative) {
    m_cumulative = std::vector<int>();
  }
}

Eddington::Eddington(const Rcpp::IntegerVector &rides, bool store_cumulative)
    : Eddington::Eddington(store_cumulative) {
  update(rides);
}

int Eddington::getEddingtonNumber() { return m_eddington_number; }

Rcpp::Nullable<Rcpp::IntegerVector> Eddington::getCumulativeEddingtonNumber() {
  // TODO: custom Rcpp::wrap for std::optional type
  return m_cumulative ? Rcpp::wrap(*m_cumulative) : R_NilValue;
}

Rcpp::DataFrame Eddington::getHashmapAsDataframe() {
  Rcpp::IntegerVector lengths, counts;
  for (auto it = m_hashmap.begin(); it != m_hashmap.end(); ++it) {
    lengths.push_back(it->first);
    counts.push_back(it->second);
  }
  return Rcpp::DataFrame::create(Rcpp::Named("length") = lengths,
                                 Rcpp::Named("count") = counts);
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

void Eddington::update(const Rcpp::IntegerVector &rides) {
  for (auto ride : rides) {
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
}
