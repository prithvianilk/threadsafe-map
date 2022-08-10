#pragma once

#include <list>
#include <mutex>
#include <vector>

using namespace std;

const int MAX_SIZE = 1e5;

class threadsafe_map {
 private:
  list<pair<int, int>> array[MAX_SIZE];
  vector<mutex> read_locks;
  vector<mutex> write_locks;
  int using_count[MAX_SIZE];

  int hash(int);

 public:
  threadsafe_map();
  int get(int);
  void put(int, int);
  void erase(int);
};

class is_equal {
 private:
  int key;

 public:
  is_equal(int);
  bool operator()(pair<int, int>&);
};