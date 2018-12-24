#!/bin/bash
rm -rf *.out
g++ -mavx512f -mavx512bw -o avx512.out test_bf16_simple.cpp
./avx512.out

icc -o bf16.out test_bf16.cpp
./bf16.out
