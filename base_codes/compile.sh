#!/bin/bash
rm *.out
g++ -std=c++11 test.cc algorithm_impls/binary_tree.cc \
               algorithm_impls/string_alg.cc \
               algorithm_impls/reverse_polish.cc \
               algorithm_impls/max_point_on_a_line.cc \
               algorithm_impls/listnode.cc \
               -g
./a.out
