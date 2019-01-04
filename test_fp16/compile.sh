#!/bin/bash
rm -rf *.out
#icpc -o test_fp16_correctness.out test_fp16_intrinsics.cc -g
g++ -mavx512f -mf16c -o test_fp16_correctness.out test_fp16_intrinsics.cc ../utils/utils.cc -g
./test_fp16_correctness.out
