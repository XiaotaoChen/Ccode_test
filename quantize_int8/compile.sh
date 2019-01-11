#!/bin/bash
rm *.out
g++ -std=c++11 -o quantize_int8.out test_quantize_int8.cc ../utils/utils.cc -g
./quantize_int8.out
