#!/bin/bash
rm *.out
g++ -std=c++11 -o mask_nbits.out test_mask_nbits.cc ../utils/utils.cc -g
./mask_nbits.out
