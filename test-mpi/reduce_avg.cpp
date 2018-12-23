// Author: Wes Kendall
// Copyright 2013 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Program that computes the average of an array of elements in parallel using
// MPI_Reduce.
//
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include "quantization.hpp"



// Creates an array of random numbers. Each number has a value from 0 - 1
float *create_rand_nums(int num_elements) {
  int baseBlockSize = QuantizationBase::QUANT_BLOCK_NUM + sizeof(QuantHead);
  float *rand_nums = NULL;
  if (sizeof(float) * num_elements < baseBlockSize) {
    rand_nums = (float *)malloc(baseBlockSize);
  } else {
    rand_nums = (float *)malloc(sizeof(float) * num_elements);
  }
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = 0.001;
  }
  return rand_nums;
}

float get_sum(const float *src, int count) {
    float sum = 0.0f;
    for (int i = 0; i < count; i++)
    {
        sum += src[i];
    }
    return sum;
}

// how many float numbers are there in each record
int RECORD_LENGTH = QuantizationBase::QUANT_BLOCK_NUM;
int block_lengths[]={3, RECORD_LENGTH};
MPI_Aint block_offsets[]={0, 12};
MPI_Datatype block_types[]={MPI_INT, MPI_CHAR};
MPI_Datatype gdt;

void quantizedSum(void *invec, void *inoutvec, int *len, MPI_Datatype *dt);

#if 1
void my_sum(void* a, void* b, int *len, MPI_Datatype * dt)
{
    return;
    //static int printed = 0;
	//float* af = (float *)a;
	//float* bf = (float *)b;
	//int i;

    //printf ("len = %d\n", *len);
    //memcpy(b, a, *len * (12 + 10000)); 
#if 0
        if (!printed) {
            printf ("len=%d\n", *len);
            printed = 1;
        }
#endif
}
#endif

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: avg num_elements_per_proc\n");
    exit(1);
  }

  system("/bin/hostname");
  int num_elements_per_proc = atoi(argv[1]);
  printf ("%d: number of elements is %d\n", getpid(), num_elements_per_proc);

  MPI_Init(NULL, NULL);


  MPI_Op op;
  MPI_Op_create(quantizedSum, 1/*commute*/, &op);

  MPI_Type_create_struct(2, block_lengths, block_offsets, block_types, &gdt);
  MPI_Type_commit(&gdt);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  float *rand_nums = NULL;
  rand_nums = create_rand_nums(num_elements_per_proc);

  // Reduce all of the local sums into the global sum
  float *global_sum = NULL;
  int baseBlockSize = QuantizationBase::QUANT_BLOCK_NUM + sizeof(QuantHead);
  if (sizeof(float) * num_elements_per_proc < baseBlockSize) {
    global_sum = (float *)malloc(baseBlockSize);
  } else {
    global_sum = (float *)malloc(sizeof(float) * num_elements_per_proc);
  }

  float *dequant_buf = NULL;
  if (sizeof(float) * num_elements_per_proc < baseBlockSize) {
    dequant_buf = (float *)malloc(baseBlockSize);
  } else {
    dequant_buf = (float *)malloc(sizeof(float) * num_elements_per_proc);
  }

  float *diff = NULL;
  if (sizeof(float) * num_elements_per_proc < baseBlockSize) {
    diff = (float *)malloc(baseBlockSize);
    memset(diff, 0, baseBlockSize);
  } else {
    diff = (float *)malloc(sizeof(float) * num_elements_per_proc);
    memset(diff, 0, sizeof(float) * num_elements_per_proc);
  }


  printf("All_Reduce(MPI_SUM) started!\n");
  struct timeval t_start, t_end;
  gettimeofday(&t_start, NULL);
  MPI_Allreduce(rand_nums, global_sum, num_elements_per_proc, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
  gettimeofday(&t_end, NULL);
  double time = t_end.tv_sec-t_start.tv_sec+(t_end.tv_usec-t_start.tv_usec)/1000000.0;
  printf("All_Reduce(MPI_SUM) sum = %lf\n", get_sum(global_sum, num_elements_per_proc));

  // Quantization Logic
  // we need (count / QUANT_BLOCK_NUM + 1) quant head
  gettimeofday(&t_start, NULL);
  QuantizationBase *quantInst = QuantizationBase::get_quantization_instance(QUANT_ROUND);
  quantInst->quantize_buffer((float *)rand_nums, (int8_t *)rand_nums, diff, num_elements_per_proc, true);
  gettimeofday(&t_end, NULL);
  double quant_time = t_end.tv_sec-t_start.tv_sec+(t_end.tv_usec-t_start.tv_usec)/1000000.0;
  // quantInst->dump_quantized_buffer((const int8_t *)rand_nums);
  // End of Quantization Logic
  size_t blockNum = QuantizationBase::QUANT_BLOCK_NUM;
  size_t blockCount = num_elements_per_proc % blockNum == 0 ? 
                        (num_elements_per_proc / blockNum) : (num_elements_per_proc / blockNum + 1);  
  gettimeofday(&t_start, NULL);
  MPI_Allreduce(rand_nums, global_sum, blockCount, gdt, op, MPI_COMM_WORLD);
  gettimeofday(&t_end, NULL);
  double userdef_op_time = t_end.tv_sec-t_start.tv_sec+(t_end.tv_usec-t_start.tv_usec)/1000000.0;

  // De-quantization Logic
  gettimeofday(&t_start, NULL);
  //quantInst->dequantize_buffer((const int8_t *)global_sum, (float *)global_sum, blockCount);
  quantInst->dequantize_buffer((const int8_t *)global_sum, (float *)dequant_buf, blockCount);
  memcpy(global_sum, dequant_buf, num_elements_per_proc * sizeof(float));
  gettimeofday(&t_end, NULL);
  double dequant_time = t_end.tv_sec-t_start.tv_sec+(t_end.tv_usec-t_start.tv_usec)/1000000.0;
  //printf("All_Reduce(user_defined Ops) sum = %lf\n", get_sum(global_sum, num_elements_per_proc));
  printf("All_Reduce(user_defined Ops) sum = %lf\n", get_sum(dequant_buf, num_elements_per_proc));
  // End of De-quantization

  // Measure Quantization Sum Time
  gettimeofday(&t_start, NULL);
  quantizedSum(rand_nums, rand_nums, (int *)&blockCount, &gdt);
  gettimeofday(&t_end, NULL);
  double quantSum_time = t_end.tv_sec-t_start.tv_sec+(t_end.tv_usec-t_start.tv_usec)/1000000.0;
  // End of Measure Quantization Sum Time
  
  double extra_time = quant_time + dequant_time + quantSum_time;

  char fileName[128] = {0};
  snprintf(fileName, 127, "./%d-%d-allreduce-ouput.txt", world_rank, num_elements_per_proc);
  FILE *fp = fopen(fileName, "w+");
  fprintf (fp, "node_id,All_Reduce(MPI_SUM),QuantTime,All_Reduce(userdef_op),DeQuantTime,Quant+AllReduce+DeQuant Time,QuantSumTime,QuantOverHead\n");
  fprintf(fp, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", world_rank, time,quant_time,userdef_op_time,dequant_time, quant_time + userdef_op_time + dequant_time, quantSum_time, extra_time);
  fclose(fp);
#if 0
  gettimeofday(&t_start, NULL);
  my_sum(rand_nums, global_sum, &num_elements_per_proc, NULL);
  gettimeofday(&t_end, NULL);
  time = t_end.tv_sec-t_start.tv_sec+(t_end.tv_usec-t_start.tv_usec)/1000000.0;
  printf ("elapsed time (sum) is %lfs\n", time);
#endif

  #if 0
  // Print the result
    printf("Total sum = :");
    int i;
    for (i=0; i<3; i++) {
      printf ("%f, ", global_sum[i]);
    }
    printf ("\n");
  #endif

  // Clean up

  //free(rand_nums);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  exit(0);
}

void quantizedSum(void *invec, void *inoutvec, int *len, MPI_Datatype *dt)
{
    if (*dt != gdt) {
        printf("Invalid data type %lu\n", (long unsigned int)*dt);
        return;
    }

    // printf("len = %d\n", *len);
    QuantHead *invecHead = (QuantHead *)invec;
    QuantHead *inoutvecHead = (QuantHead *)inoutvec;
    if (invecHead->magic != QUANT_HEAD_MAGIC || inoutvecHead->magic != QUANT_HEAD_MAGIC) {
        printf("quantizedSum:Wrong quantization head magic number!\n");
        return;
    }

    //dequantize, sum and quantize
    QuantizationBase *quantInst = QuantizationBase::get_quantization_instance(QUANT_ROUND);
    //quantInst->quantize_sum((const int8_t *)invec, (int8_t *)inoutvec, *len);
     quantInst->quantize_sum2((const int8_t *)invec, (int8_t *)inoutvec, *len);
/*
    size_t inCount        = quantInst->get_dataCount_in_quantized_buffer((const int8_t*)invec, *len);
    size_t outCount       = quantInst->get_dataCount_in_quantized_buffer((const int8_t*)inoutvec, *len);
    if (inCount != outCount) {
       printf("inCount is not equal to outCount\n");
       printf("inCount = %lu outCount = %lu\n", inCount, outCount);
       return;
    }
    // printf("inCount = %lu outCount = %lu\n", inCount, outCount);

//    quantInst->dump_quantized_buffer((const int8_t *)invec);
//    quantInst->dump_quantized_buffer((const int8_t *)inoutvec);

    float  *dequantBuf1   = (float *)malloc(inCount * sizeof(float));
    float  *dequantBuf2   = (float *)malloc(outCount * sizeof(float));

    quantInst->dequantize_buffer((int8_t*)invec, dequantBuf1, *len);
    quantInst->dequantize_buffer((int8_t*)inoutvec, dequantBuf2, *len);

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < inCount; ++i) {
        dequantBuf1[i] += dequantBuf2[i];
    }
    quantInst->quantize_buffer(dequantBuf1, (int8_t*)inoutvec, outCount, *len);
    // printf("Dump Quantized Sum Result:\n");
    // quantInst->dump_quantized_buffer((const int8_t *)inoutvec);
    free(dequantBuf1);
    free(dequantBuf2);

    // printf("Quantized Sum Finished!\n");
*/
}
