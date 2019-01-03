#!/bin/bash
rm -rf *.out
#g++ -mavx512f -mavx512bw -o avx512.out test_bf16_simple.cpp
#./avx512.out
#
#icc -o bf16.out test_bf16.cpp
#./bf16.out
#
#g++ -mavx512f -mavx512bw -o array_convert.out test_array_convert.cpp
#./array_convert.out

g++ -mavx512f -mavx512bw -o intrinsic_correctness.out test_intrinsic_correctness.cc -g
./intrinsic_correctness.out
