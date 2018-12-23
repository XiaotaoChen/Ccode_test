#!/bin/bash
workspace=$(pwd)
hostfile=$1
single_script=$2
num_proc=2
proc_per_node=2
mpirun \
    -n ${num_proc} \
    -ppn ${proc_per_node} \
    -genv I_MPI_FABRICS=shm \
    -genv OMP_NUM_THREADS=10 \
    -hostfile ${workspace}/${hostfile} \
    ${workspace}/${single_script}

#mpirun \
#    -n ${num_proc} \
#    -ppn ${proc_per_node} \
#    -genv I_MPI_FABRICS=shm \
#    -genv OMP_NUM_THREADS=20 \
#    ${workspace}/${single_script}
