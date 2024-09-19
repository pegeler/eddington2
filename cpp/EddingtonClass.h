#pragma once

#include <iostream>
#include <optional>
#include <unordered_map>
#include <vector>

class Eddington {
public:
  // Constructors
  Eddington();
  Eddington(bool store_cumulative);
  Eddington(const std::vector<int> &rides, bool store_cumulative = false);

  // Getters
  int getEddingtonNumber();
  std::optional<std::vector<int>> getCumulativeEddingtonNumber();

  // Member functions
  int getNumberToNext();
  int getNumberToTarget(int target);
  void update(const std::vector<int> &rides);
  void update(std::istream& rides);
  void print();

private:
  int m_n_above = 0;
  int m_eddington_number = 0;
  std::unordered_map<int, int> m_hashmap;
  std::optional<std::vector<int>> m_cumulative;
};
