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
  int getEddingtonNumber() {return m_eddington_number;};
  const std::optional<std::vector<int>> &getCumulativeEddingtonNumber() const {
    return m_cumulative;
  };

  // Member functions
  int getNumberToNext();
  int getNumberToTarget(int target);
  void update(int ride);
  void update(const std::vector<int> &rides);
  void update(std::istream& rides);
  void print();

private:
  int m_n_above = 0;
  int m_eddington_number = 0;
  std::unordered_map<int, int> m_hashmap;
  std::optional<std::vector<int>> m_cumulative;
};
