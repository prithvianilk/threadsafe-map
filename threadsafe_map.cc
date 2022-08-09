#include "threadsafe_map.h"

#include <set>

threadsafe_map::threadsafe_map() : array(new int[N]) {
  for (int i = 0; i < N; ++i) {
    array[i] = -1;
  }
}

threadsafe_map::~threadsafe_map() { delete[] array; }

int threadsafe_map::hash(int key) { return key % N; }

int threadsafe_map::get(int key) { return array[hash(key)]; }

void threadsafe_map::put(int key, int value) { array[hash(key)] = value; }

void threadsafe_map::erase(int key) { array[hash(key)] = -1; }
