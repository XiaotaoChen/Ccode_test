#!/bin/bash

export KMP_AFFINITY=granularity=fine,noduplicates,compact,1,0

cxxs=(icpc g++)
num_threads=(56 32 28 16 8 4 2 1)
for cxx in ${cxxs[@]}
do
  echo "================================"
  echo " running with ${cxx}"
  echo "================================"
  for num_thread in ${num_threads[@]}
  do
    ./memory_test.${cxx} ${num_thread} 30
  done
done
