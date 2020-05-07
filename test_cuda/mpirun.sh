#!/bin/bash

workspace=/mnt/truenas/scratch/xiaotao.chen/Repositories/Ccode_test/test_cuda

num_proc=1
hostfile=local.txt
single_script=./test


/root/3rdparty/openmpi4.0/bin/mpirun -np ${num_proc} \
    --allow-run-as-root \
    --npernode 2 \
    --hostfile ${hostfile} \
    -bind-to none -map-by slot \
    -x NCCL_DEBUG=INFO \
    -x LD_LIBRARY_PATH \
    -x PATH \
    -x PYTHONPATH \
    -x OMP_NUM_THREADS=1 \
    -mca pml ob1 \
    -mca btl ^openib \
    ${single_script}

