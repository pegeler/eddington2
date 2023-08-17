#pragma once
// [[Rcpp::interfaces(r, cpp)]]

#include <Rcpp.h>

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
  bool isSatisfied(int target);
  void update(const Rcpp::IntegerVector &rides);

private:
  int m_n_above = 0;
  int m_eddington_number = 0;
  bool m_store_cumulative = false;
  std::unordered_map<int, int> m_hashmap;
  Rcpp::IntegerVector m_cumulative;
};
