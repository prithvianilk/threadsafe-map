GCC = g++

test_2: threadsafe_map
	$(GCC) -std=c++20 -Wall -o threadsafe_map test_2.cc threadsafe_map.o

test_1: threadsafe_map
	$(GCC) -std=c++20 -Wall -o threadsafe_map test_1.cc threadsafe_map.o

threadsafe_map: threadsafe_map.cc threadsafe_map.h
	$(GCC) -std=c++20 -Wall -c -o threadsafe_map.o threadsafe_map.cc
