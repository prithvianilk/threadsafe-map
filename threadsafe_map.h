#pragma once

#include <list>

using namespace std;

class threadsafe_map {
 private:
  static const int MAX_SIZE = 1e5;
  list<pair<int, int>>* array;
  int hash(int);

 public:
  threadsafe_map();
  ~threadsafe_map();
  int get(int);
  void put(int, int);
  void erase(int);
};