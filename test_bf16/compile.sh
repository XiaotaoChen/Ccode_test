#!/bin/bash
g++ -mavx512f -mavx512bw -o avx512.out test_bf16_simple.cpp
./avx512.out

icc -o bf16.out test_bf16.c
./bf16.out
