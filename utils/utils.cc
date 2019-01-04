#include <cstring>
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

} // namespace utils