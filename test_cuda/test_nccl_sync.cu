#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include <map>
#include <assert.h>
#include <string>
#include <thread>
#include <string>

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

template<class T>
class GlobalSharedRank {
 public:
  T Register(const std::string &key, int ndev) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = registry_.find(key);
    if (it != registry_.end()) {
      T* tmpT = it->second;
      *tmpT = (*tmpT == ndev - 1) ? 0 : *tmpT + 1;
      return *tmpT;
    }
    T *newT = new T(0);
    registry_[key] = newT;
    return *newT;
  }
  ~GlobalSharedRank() {
    for (auto it = registry_.begin(); it != registry_.end(); it++) {
      T *ptr = it->second;
      delete ptr;
    }
  }
 private:
  std::mutex mutex_;
  std::map<std::string, T*> registry_;
};

__global__ void do_average(float* data, int ndev, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid > size) return;
    data[tid] /= ndev;
}

class GlobalShared {
private:
    float** tensors;
    int tensor_size=-1;
    bool* ready_flags;
    ncclComm_t* comms = nullptr;
    cudaStream_t* s = nullptr;
    int ndev;
    bool mean_ready;
    std::mutex mutex_;

public:
    GlobalShared(int ndev, int size):ndev(ndev), tensor_size(size) {
        comms = new ncclComm_t[ndev];
        int devs[ndev];
        s = new cudaStream_t[ndev];
        ready_flags = new bool[ndev];
        tensors = new float*[ndev];

        for (int i=0; i<ndev; i++) {
            devs[i]=i;
            CUDACHECK(cudaSetDevice(i));
            CUDACHECK(cudaStreamCreate(s+i));
        }
        NCCLCHECK(ncclCommInitAll(comms, ndev, devs));

        for (int i=0; i<ndev; i++)
            std::cout << "cudastream " << i << " : " << s+i << std::endl;
    }

    GlobalShared(const GlobalShared& other) {
        *this = other;
    }

    const GlobalShared& operator=(const GlobalShared& other) {
        *this = other;
        return *this;
    }

    ~GlobalShared() {
        std::cout << "~global shared called" << std::endl;
        for(int i = 0; i < ndev; ++i) {
            ncclCommDestroy(comms[i]);
        }
        delete[] comms;
        delete[] s;
        delete[] tensors;
        delete[] ready_flags;
    }

    void set_tensor_ptr(float* tensor, int rank) {
        std::lock_guard<std::mutex> lck(mutex_);
        tensors[rank] = tensor;
        ready_flags[rank] = true;
    }

    void get_mean(int rank) {
        std::unique_lock<std::mutex> lck(mutex_);
        while(!MeanReady()) {}
        ready_flags[rank] = false;
        resetMeanReady();
    }

    bool MeanReady() {
        if (mean_ready) return true;
        for (int i=0; i<ndev; i++) {
            bool tmp = ready_flags[i];
            if (!tmp)  return false;
            // if (!ready_flags[key][i])  return false;
        }

        NCCLCHECK(ncclGroupStart());
        for (int i = 0; i < ndev; ++i) {
            float* buffi = tensors[i];
            NCCLCHECK(ncclAllReduce((const void*)buffi, (void*)buffi, tensor_size, ncclFloat, ncclSum, comms[i], s[i]));
            // NCCLCHECK(ncclAllReduce((const void*)buff[i], (void*)buff[i], size, ncclFloat, ncclSum, comms[i], s[i]));
        }
        NCCLCHECK(ncclGroupEnd());

        for (int i = 0; i < ndev; ++i) {
            CUDACHECK(cudaSetDevice(i));
            std::cout << "sync " << i << ": " << &(s[i]) << std::endl;
            CUDACHECK(cudaStreamSynchronize(s[i]));
        }
    
        // do average
        for (int i=0; i<ndev; i++) do_average<<<1, 256>>>(tensors[i], ndev, tensor_size);

        mean_ready = true;
        return true;
    }

    void resetMeanReady() {
        for (int i=0; i<ndev; i++) {
            if (ready_flags[i]) return;
        }
        mean_ready = false;
    }

};

template <typename T>
class singleton {
private:
    singleton(){}
    ~singleton(){}
public:
    static T* getInstance(int ndev, int size) {
        static T m_instance = T(ndev, size);
        return &m_instance;
    }
};


static GlobalSharedRank<int> global_shared_rank;


void sync_func(int dev_id, int ndev) {
    int size = 32;
    float* buff;
    // host sendbuff
    float* h_sendbuff = new float[size];
    std::fill_n(h_sendbuff, size, 1 + dev_id);

    CUDACHECK(cudaSetDevice(dev_id));
    CUDACHECK(cudaMalloc(&buff, size * sizeof(float)));
    CUDACHECK(cudaMemcpy(buff, h_sendbuff, size * sizeof(float), cudaMemcpyHostToDevice));
    
    static GlobalShared* gs = singleton<GlobalShared>::getInstance(ndev, size);
    (*gs).set_tensor_ptr(buff, dev_id);

    (*gs).get_mean(dev_id);

    std::cout << dev_id << "/" << ndev << " allreduce:\n";
    print_result(buff, 10);
}


void test_sync() {
    int ndev = 1;
    std::thread threads[ndev];
    for (int i=0; i<ndev; i++) {
        threads[i] = std::thread(sync_func, i, ndev);
    }
    
    for (int i=0; i<ndev; i++) {
        threads[i].join();
    }
}

int main(int argc, char* argv[])
{
    test_sync();
  
  return 0;
}