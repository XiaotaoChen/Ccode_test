/*!
 *  Copyright (c) 2015 by Contributors
 * \file bf16.h
 * \brief definition of utils tools.
 *
 * \author Xiaotao Chen
 */
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <ctime>
using std::vector;
namespace utils {

float average(const vector<double> &timing);

class Time {
public:
  Time();
  void start();
  void stop();
  double get_time();
private:
  struct timespec start_t, stop_t;
};

void* alloc_mem(size_t size, int alignment);

void free_mem(void* ptr);

void init_mem(void* ptr, size_t len);

}  // namespace utils

#endif // UTILS_H