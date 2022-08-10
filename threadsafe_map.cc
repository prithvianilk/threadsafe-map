#include "threadsafe_map.h"

#include <algorithm>
#include <functional>
#include <list>
#include <mutex>
#include <vector>

using namespace std;

threadsafe_map::threadsafe_map()
    : read_locks(vector<mutex>(MAX_SIZE)),
      write_locks(vector<mutex>(MAX_SIZE)) {}

int threadsafe_map::hash(int key) { return key % MAX_SIZE; }

int threadsafe_map::get(int key) {
  int hashed_key = hash(key);
  read_locks[hashed_key].lock();
  if (using_count[hashed_key]++ == 0) {
    write_locks[hashed_key].lock();
  }
  read_locks[hashed_key].unlock();
  auto list = array[hashed_key];
  auto is_equal = [&](auto& kv_pair) { return kv_pair.first == key; };
  auto it = find_if(list.begin(), list.end(), is_equal);
  int ans = 0;
  if (it != list.end()) {
    ans = (*it).second;
  }
  read_locks[hashed_key].lock();
  if (--using_count[hashed_key] == 0) {
    write_locks[hashed_key].unlock();
  }
  read_locks[hashed_key].unlock();
  return ans;
}

void threadsafe_map::put(int key, int value) {
  int hashed_key = hash(key);
  write_locks[hashed_key].lock();
  array[hashed_key].push_front({key, value});
  write_locks[hashed_key].unlock();
}

void threadsafe_map::erase(int key) {
  auto is_equal = [&](auto& kv_pair) { return kv_pair.first == key; };
  int hashed_key = hash(key);
  write_locks[hashed_key].lock();
  array[hashed_key].remove_if(is_equal);
  write_locks[hashed_key].unlock();
}
