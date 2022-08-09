#pragma once

class threadsafe_map {
 private:
  static const int N = 1e5;
  int* array;
  int hash(int);

 public:
  threadsafe_map();
  ~threadsafe_map();
  int get(int);
  void put(int, int);
  void erase(int);
};