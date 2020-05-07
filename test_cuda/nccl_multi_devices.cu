#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <thread>
#include "cuda_runtime.h"
#include "nccl.h"

#include "mpi.h"
#include <unistd.h>
#include <stdint.h>

#define CUDACHECK(cmd) do {                         \
  cudaError_t e = cmd;                              \
  if( e != cudaSuccess ) {                          \
    printf("Failed: Cuda error %s:%d '%s'\n",             \
        __FILE__,__LINE__,cudaGetErrorString(e));   \
    exit(EXIT_FAILURE);                             \
  }                                                 \
} while(0)


#define NCCLCHECK(cmd) do {                         \
  ncclResult_t r = cmd;                             \
  if (r!= ncclSuccess) {                            \
    printf("Failed, NCCL error %s:%d '%s'\n",             \
        __FILE__,__LINE__,ncclGetErrorString(r));   \
    exit(EXIT_FAILURE);                             \
  }                                                 \
} while(0)

#define MPICHECK(cmd) do {                          \
  int e = cmd;                                      \
  if( e != MPI_SUCCESS ) {                          \
    printf("Failed: MPI error %s:%d '%d'\n",        \
        __FILE__,__LINE__, e);   \
    exit(EXIT_FAILURE);                             \
  }                                                 \
} while(0)

static uint64_t getHostHash(const char* string) {
  // Based on DJB2, result = result * 33 + char
  uint64_t result = 5381;
  for (int c = 0; string[c] != '\0'; c++){
    result = ((result << 5) + result) + string[c];
  }
  return result;
}


static void getHostName(char* hostname, int maxlen) {
  gethostname(hostname, maxlen);
  for (int i=0; i< maxlen; i++) {
    if (hostname[i] == '.') {
        hostname[i] = '\0';
        return;
    }
  }
}

void print_result(float* buff, int size) {
  float* h_buff = new float[size];
  CUDACHECK(cudaMemcpy(h_buff, buff, sizeof(float) * size, cudaMemcpyDeviceToHost));
  std::cout << "buff size: " << size << std::endl;
  for (int i=0; i<size; i++) {
    std::cout << h_buff[i] << " ";
  }
  std::cout << std::endl;
  delete[] h_buff;
}

void test_nccl_multi_device() {
  ncclComm_t comms[4];


  //managing 4 devices
  int nDev = 4;
  int size = 32*1024*1024;
  int devs[4] = { 0, 1, 2, 3 };


  //allocating and initializing device buffers
  float** sendbuff = (float**)malloc(nDev * sizeof(float*));
  float** recvbuff = (float**)malloc(nDev * sizeof(float*));
  cudaStream_t* s = (cudaStream_t*)malloc(sizeof(cudaStream_t)*nDev);

  // host sendbuff
  float* h_sendbuff = new float[size];
  std::fill_n(h_sendbuff, size, 1);




  for (int i = 0; i < nDev; ++i) {
    CUDACHECK(cudaSetDevice(i));
    CUDACHECK(cudaMalloc(sendbuff + i, size * sizeof(float)));
    CUDACHECK(cudaMalloc(recvbuff + i, size * sizeof(float)));
    // CUDACHECK(cudaMemset(sendbuff[i], 1, size * sizeof(float)));
    CUDACHECK(cudaMemcpy(sendbuff[i], h_sendbuff, size * sizeof(float), cudaMemcpyHostToDevice));
    CUDACHECK(cudaMemset(recvbuff[i], 0, size * sizeof(float)));
    CUDACHECK(cudaStreamCreate(s+i));
  }

  std::cout << "sendbuff: " << std::endl;
  print_result(sendbuff[0], 10);
  std::cout << "recvbuff: " << std::endl;
  print_result(recvbuff[0], 10);

  //initializing NCCL
  NCCLCHECK(ncclCommInitAll(comms, nDev, devs));


   //calling NCCL communication API. Group API is required when using
   //multiple devices per thread
  NCCLCHECK(ncclGroupStart());
  for (int i = 0; i < nDev; ++i)
    // NCCLCHECK(ncclAllReduce((const void*)sendbuff[i], (void*)recvbuff[i], size, ncclFloat, ncclSum,
    //     comms[i], s[i]));
    NCCLCHECK(ncclAllReduce((const void*)sendbuff[i], (void*)sendbuff[i], size, ncclFloat, ncclSum,
        comms[i], s[i]));
  NCCLCHECK(ncclGroupEnd());

  for (int i=0; i<nDev; i++) {
    std::cout << "after allreduce device id: " << i << " recvbuff: " << std::endl;
    print_result(recvbuff[0], 10);
  }
  for (int i=0; i<nDev; i++) {
    std::cout << "after allreduce device id: " << i << " sendbuff: " << std::endl;
    print_result(sendbuff[0], 10);
  }
  


  //synchronizing on CUDA streams to wait for completion of NCCL operation
  for (int i = 0; i < nDev; ++i) {
    CUDACHECK(cudaSetDevice(i));
    CUDACHECK(cudaStreamSynchronize(s[i]));
  }


  //free device buffers
  for (int i = 0; i < nDev; ++i) {
    CUDACHECK(cudaSetDevice(i));
    CUDACHECK(cudaFree(sendbuff[i]));
    CUDACHECK(cudaFree(recvbuff[i]));
  }


  //finalizing NCCL
  for(int i = 0; i < nDev; ++i)
      ncclCommDestroy(comms[i]);
  
  printf("test multi device Success \n");
}

void test_nccl_multi_process() {
  int size = 32*1024*1024;
  int myRank, nRanks, localRank = 0;


  //initializing MPI
  // MPICHECK(MPI_Init(&argc, &argv));
  MPICHECK(MPI_Init(NULL, NULL));
  MPICHECK(MPI_Comm_rank(MPI_COMM_WORLD, &myRank));
  MPICHECK(MPI_Comm_size(MPI_COMM_WORLD, &nRanks));

  std::cout << "myRank: " << myRank << " nRanks: " << nRanks << std::endl;

  //calculating localRank based on hostname which is used in selecting a GPU
  uint64_t hostHashs[nRanks];
  char hostname[1024];
  getHostName(hostname, 1024);
  hostHashs[myRank] = getHostHash(hostname);

  std::cout << "hostname: " << hostname << std::endl;
  for (int i=0; i<nRanks; i++) {
    std::cout << "rank: " << i << " hash: " << hostHashs[i] << std::endl;
  }

  MPICHECK(MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, hostHashs, sizeof(uint64_t), MPI_BYTE, MPI_COMM_WORLD));
  for (int p=0; p<nRanks; p++) {
     if (p == myRank) break;
     if (hostHashs[p] == hostHashs[myRank]) localRank++;
  }

  for (int i=0; i<nRanks; i++) {
    std::cout << "rank: " << i << " hash: " << hostHashs[i] << std::endl;
  }


  ncclUniqueId id;
  ncclComm_t comm;
  float *sendbuff, *recvbuff;
  cudaStream_t s;


  //get NCCL unique ID at rank 0 and broadcast it to all others
  if (myRank == 0) ncclGetUniqueId(&id);
  MPICHECK(MPI_Bcast((void *)&id, sizeof(id), MPI_BYTE, 0, MPI_COMM_WORLD));


  //picking a GPU based on localRank, allocate device buffers
  CUDACHECK(cudaSetDevice(localRank));
  CUDACHECK(cudaMalloc(&sendbuff, size * sizeof(float)));
  CUDACHECK(cudaMalloc(&recvbuff, size * sizeof(float)));
  CUDACHECK(cudaStreamCreate(&s));


  //initializing NCCL
  NCCLCHECK(ncclCommInitRank(&comm, nRanks, id, myRank));


  //communicating using NCCL
  NCCLCHECK(ncclAllReduce((const void*)sendbuff, (void*)recvbuff, size, ncclFloat, ncclSum,
        comm, s));


  //completing NCCL operation by synchronizing on the CUDA stream
  CUDACHECK(cudaStreamSynchronize(s));


  //free device buffers
  CUDACHECK(cudaFree(sendbuff));
  CUDACHECK(cudaFree(recvbuff));


  //finalizing NCCL
  ncclCommDestroy(comm);


  //finalizing MPI
  MPICHECK(MPI_Finalize());


  printf("[MPI Rank %d] Success \n", myRank);

}


__global__ void do_average(float* data, int ndev, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid >= size) return;
    data[tid] /= ndev;
}


void nccl_comm_multi_thread(int myRank, int nRanks, ncclUniqueId& id) {
  // ncclUniqueId id;
  ncclComm_t comm;
  float *sendbuff;
  cudaStream_t s;
  int size = 32;

  float* h_sendbuff = new float[size];
  std::fill_n(h_sendbuff, size, 1 + myRank);


  //picking a GPU based on localRank, allocate device buffers
  CUDACHECK(cudaSetDevice(myRank));
  CUDACHECK(cudaMalloc(&sendbuff, size * sizeof(float)));
  CUDACHECK(cudaMemcpy(sendbuff, h_sendbuff, size * sizeof(float), cudaMemcpyHostToDevice));
  CUDACHECK(cudaStreamCreate(&s));


  //initializing NCCL
  NCCLCHECK(ncclCommInitRank(&comm, nRanks, id, myRank));


  //communicating using NCCL
  NCCLCHECK(ncclAllReduce((const void*)sendbuff, (void*)sendbuff, size, ncclFloat, ncclSum,
        comm, s));


  //completing NCCL operation by synchronizing on the CUDA stream
  CUDACHECK(cudaStreamSynchronize(s));

  do_average<<<1, 256>>>(sendbuff, nRanks, size);

  std::cout << "[mutip thread Rank " << myRank << "] Success \n";
  if (myRank == 0) print_result(sendbuff, size);

  //free device buffers
  CUDACHECK(cudaFree(sendbuff));

  delete[] h_sendbuff;


  //finalizing NCCL
  ncclCommDestroy(comm);
}

void test_nccl_multi_thread() {
  int ndev = 8;
  ncclUniqueId id;
  ncclGetUniqueId(&id);

  std::thread threads[ndev];
    for (int i=0; i<ndev; i++) {
        threads[i] = std::thread(nccl_comm_multi_thread, i, ndev, std::ref(id));
    }
    
    for (int i=0; i<ndev; i++) {
        threads[i].join();
    }
}

int main(int argc, char* argv[])
{
  // test_nccl_multi_device();
  // test_nccl_multi_process();
  test_nccl_multi_thread();

  
  return 0;
}