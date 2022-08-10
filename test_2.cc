#include <iostream>
#include <thread>

#include "threadsafe_map.h"

using namespace std;

int main() {
  threadsafe_map map;
  mutex stdout_mutex;
  const auto N = 100;
  thread threads[N];
  for (int i = 0; i < N; ++i) {
    if (i % 3 == 0) {
      threads[i] = thread([&](int j) { map.put(69, j + 1); }, i);
      stdout_mutex.lock();
      cout << "Putting: " << i + 1 << '\n';
      stdout_mutex.unlock();
    } else {
      threads[i] = thread([&]() {
        int value = map.get(69);
        stdout_mutex.lock();
        std::cout << "Getting " << value << '\n';
        stdout_mutex.unlock();
      });
    }
  }
  for (int i = 0; i < N; ++i) {
    threads[i].join();
  }
  std::cout << "Final: " << map.get(69) << "\n";
  return 0;
}