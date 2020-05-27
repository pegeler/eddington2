CXX = gcc

.PHONY: all

all: eddington eddington-deprecated

eddington-deprecated: eddington-deprecated.c
	$(CXX) $@.c -o $@

eddington: eddington.c
	$(CXX) $@.c -o $@
