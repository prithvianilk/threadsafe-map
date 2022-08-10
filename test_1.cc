#include <iostream>

#include "threadsafe_map.h"

using namespace std;

int main() {
  threadsafe_map map;
  map.put(69, 420);
  cout << map.get(69) << '\n';
  map.erase(69);
  cout << map.get(69) << '\n';
  return 0;
}