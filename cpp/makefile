CXX = g++
CXXFLAGS=-std=c++11 -O2
DEPS=

.PHONY: all

all: eddington stream

eddington: eddington.cpp EddingtonClass.cpp
	$(CXX) $(CXXFLAGS) $@.cpp EddingtonClass.cpp -o $@

stream: stream.cpp
	$(CXX) $(CXXFLAGS) $@.cpp -o $@
