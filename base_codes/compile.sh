#!/bin/bash
rm *.out
g++ -std=c++11 test.cc algorithm_impls/binary_tree.cc -g
./a.out
