#include "threadsafe_map.h"

#include <algorithm>
#include <functional>
#include <list>

using namespace std;

threadsafe_map::threadsafe_map() : array(new list<pair<int, int>>[MAX_SIZE]) {}

threadsafe_map::~threadsafe_map() { delete[] array; }

int threadsafe_map::hash(int key) { return key % MAX_SIZE; }

int threadsafe_map::get(int key) {
  int hashed_key = hash(key);
  for (auto [_key, value] : array[hashed_key]) {
    if (_key == key) {
      return value;
    }
  }
  return 0;
}

void threadsafe_map::put(int key, int value) {
  array[hash(key)].push_front({key, value});
}

void threadsafe_map::erase(int key) {
  auto& list = array[hash(key)];
  list.remove_if([&](auto& kv_pair) { return kv_pair.first == key; });
}
