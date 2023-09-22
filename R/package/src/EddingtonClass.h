#pragma once

#include <Rcpp.h>
#include <optional>
#include <unordered_map>
#include <vector>

class Eddington {
public:
  // Constructors
  Eddington();
  Eddington(bool store_cumulative);
  Eddington(const Rcpp::IntegerVector &rides, bool store_cumulative = false);

  // Getters
  int getEddingtonNumber();
  Rcpp::Nullable<Rcpp::IntegerVector> getCumulativeEddingtonNumber();
  Rcpp::DataFrame getHashmapAsDataframe();

  // Member functions
  int getNumberToNext();
  int getNumberToTarget(int target);
  void update(const Rcpp::IntegerVector &rides);

private:
  int m_n_above = 0;
  int m_eddington_number = 0;
  std::unordered_map<int, int> m_hashmap;
  std::optional<std::vector<int>> m_cumulative;
};
