CXX = gcc

.PHONY: all

all: eddington-deprecated eddington-hashmap eddington-tree eddington

eddington-deprecated: eddington-deprecated.c
	$(CXX) $@.c -o $@

eddington-hashmap: eddington-hashmap.c hashmap.c hashmap.h
	$(CXX) $@.c hashmap.c -o $@

eddington-tree: eddington-tree.c tree.c tree.h
	$(CXX) $@.c tree.c -o $@

eddington: eddington.c
	$(CXX) $@.c -o $@
