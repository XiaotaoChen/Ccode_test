#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <cstdio>

int partition_cpu(int total_count, int partition_idx, int partition_nums, cpu_set_t& cpuset) {
    int size = CPU_ALLOC_SIZE(total_count);
    CPU_ZERO_S(size, &cpuset);

    int count_per_thread = total_count / partition_nums;
    for (int cpu_id = partition_idx * count_per_thread; cpu_id < (partition_idx+1)* count_per_thread; cpu_id++) {
        CPU_SET_S(cpu_id, size, &cpuset);
    }
    return size;
}

int bind_cpu(const pthread_t& pthread, int total_count, int partition_idx, int partition_nums) {
    cpu_set_t cpuset;
    int size = partition_cpu(total_count, partition_idx, partition_nums, cpuset);
    int rc = pthread_setaffinity_np(pthread, sizeof(cpu_set_t), &cpuset);
    printf("thread id: %d  CPU_COUNT() of set: %d\n", partition_idx, CPU_COUNT_S(size, &cpuset));
    if (rc != 0) {
      printf("Error calling pthread_setaffinity_np: %d\n", rc);
    }
    return rc;
}


int test_thread() {
  constexpr unsigned num_threads = 8;
  int total_count = 96;
  int count_per_thread = total_count / num_threads;
  // A mutex ensures orderly access to std::cout from multiple threads.
  std::mutex iomutex;
  std::vector<std::thread> threads(num_threads);
  for (unsigned i = 0; i < num_threads; ++i) {
    threads[i] = std::thread([&iomutex, i] {
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
      while (1) {
        {
          // Use a lexical scope and lock_guard to safely lock the mutex only
          // for the duration of std::cout usage.
          std::lock_guard<std::mutex> iolock(iomutex);
          std::cout << "Thread #" << i << ": on CPU " << sched_getcpu() << "\n";
        }

        // Simulate important work done by the tread by sleeping for a bit...
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
      }
    });

    // Create a cpu_set_t object representing a set of CPUs. Clear it and mark
    // only CPU i as set.
    int rc = bind_cpu(threads[i].native_handle(), total_count, i, num_threads);
  }

  for (auto& t : threads) {
    t.join();
  }
  return 0;
}

int main() {
    // simple_test();
    test_thread();
}

