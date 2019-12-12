#ifndef EddingtonClass_H
#define EddingtonClass_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

class Eddington {
  private:

    int above=0;
    int running=0;
    std::vector<int> cumulative;
    std::unordered_map<int, int> H = std::unordered_map<int, int>(150);

  public:

    int E();
    std::vector<int> E_vec();
    void update(std::istream& input, bool const verbose);
    void print();
    int next();
    int required(int target);

};

#endif
