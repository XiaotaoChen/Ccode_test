#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>

#include "cuda_runtime.h"
#include "nccl.h"


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



__global__ void do_average(float* data, int ndev, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid >= size) return;
    data[tid] /= ndev;
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

template <typename T>
class singleton {
private:
    singleton(){}
    ~singleton(){}
public:
    static T& getInstance(int ndev) {
        static T m_instance = T(ndev);
        return m_instance;
    }
};

class GlobalShared {
private:
    int ndev;
    ncclUniqueId uid;
    ncclComm_t* comms;
    cudaStream_t* streams;
    std::vector<bool> inited;
    int NUM_THREADS = 256;

public:
    GlobalShared(int ndev): ndev(ndev) {
            ncclGetUniqueId(&uid);
            inited = std::vector<bool>(ndev, false);
            comms = new ncclComm_t[ndev];
            streams = new cudaStream_t[ndev];
    }

    ~GlobalShared() {
        for(int i=0; i < ndev; i++) {
            if (inited[i]) ncclCommDestroy(comms[i]);
        }
        delete comms;
        delete streams;
    }

    void init(int rank) {
        if (!inited[rank]) {
            CUDACHECK(cudaSetDevice(rank));
            CUDACHECK(cudaStreamCreate(&streams[rank]));
            NCCLCHECK(ncclCommInitRank(&comms[rank], ndev, uid, rank));
            inited[rank] = true;
        }
    }

    void reduce(float* buff, int size, int rank) {
        NCCLCHECK(ncclAllReduce((const void*)buff, (void*)buff, size, ncclFloat, ncclSum, comms[rank], streams[rank]));
        CUDACHECK(cudaStreamSynchronize(streams[rank]));

        do_average<<<(size+NUM_THREADS-1)/NUM_THREADS, NUM_THREADS>>>(buff, ndev, size);
    }

};

void bn_forward(int rank, int ndev) {

    int repeat = 10;
    std::vector<int> arr(10, 0);
    for (int i=0; i < repeat; i++) arr[i] = i;

    // std::random_device rd;
    // std::mt19937 g(rd());
    // std::shuffle(arr.begin(), arr.end(), g);
    // for (int i=0; i<repeat; i++) std::cout << arr[i] << " ";
    // std::cout << std::endl;

    for (int i = 0; i < repeat; i++) {
    // for (auto& i: arr) {

        static GlobalShared gs = singleton<GlobalShared>::getInstance(ndev);
        gs.init(rank);
        
        int size = 32 * (i+1);
        // if (rank == 0) {
            std::cout << rank << " all reduce i: " << i << " size: " << size << std::endl;
        // }
        
        float *buff, *h_buff;
        h_buff = new float[size];
        std::fill_n(h_buff, size, (1+rank) + i * ndev);

        CUDACHECK(cudaSetDevice(rank));
        CUDACHECK(cudaMalloc(&buff, size * sizeof(float)));
        CUDACHECK(cudaMemcpy(buff, h_buff, size * sizeof(float), cudaMemcpyHostToDevice));
        
        gs.reduce(buff, size, rank);

        if (rank == 0) {
            print_result(buff, 10);
        }

        CUDACHECK(cudaFree(buff));

        delete[] h_buff;
    }
}

void test_sync_bn() {
    int ndev = 2;
    std::thread threads[ndev];
    for (int i=0; i<ndev; i++) {
        threads[i] = std::thread(bn_forward, i, ndev);
    }
    for (int i=0; i<ndev; i++) {
        threads[i].join();
    }
}

int main() {
    test_sync_bn();

    return 0;
}