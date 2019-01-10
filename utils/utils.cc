#include <cstring>
#include <stdlib.h>  // rand, aligned_alloc
#include "utils.h"

namespace utils {
float average(const vector<double> &timing) {
  double avg = 0;
  for(auto it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();
  //return us
  avg /= 1000;
  return avg;
}

Time::Time() {
  memset(&(this->start_t), 0, sizeof(struct timespec));
  memset(&(this->stop_t), 0, sizeof(struct timespec));
}

void Time::start(){
  clock_gettime(CLOCK_REALTIME, &(this->start_t));
}

void Time::stop(){
  clock_gettime(CLOCK_REALTIME, &(this->stop_t));
}

double Time::get_time(){
  double time_nsec = (stop_t.tv_sec - start_t.tv_sec) * 1000000000 + (stop_t.tv_nsec -start_t.tv_nsec);
  return time_nsec;
}

void* alloc_mem(size_t size, int alignment){
  if (size % alignment == 0) {
    return aligned_alloc(alignment, size);
  }
  else {
    size_t new_size = (size / alignment + 1 ) * alignment;
    return aligned_alloc(alignment, new_size);
  }
}

void init_mem(void* ptr, size_t len) {
  char* ch_ptr = reinterpret_cast<char*>(ptr);
  srand((unsigned)time(NULL));
  for(int i=0; i < len; i++){
    ch_ptr[i] = rand();
  }
}


} // namespace utils