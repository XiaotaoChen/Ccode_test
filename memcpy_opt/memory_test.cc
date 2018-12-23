#include <iostream>
#include <iomanip>        //setw
#include <vector>
#include <memory>
#include <string.h>       //memset
#include <omp.h>
#include <sys/time.h>


using namespace std;


float average(const vector<double> &timing) {
  double avg = 0;
  for(auto it = timing.begin(); it != timing.end(); it++) avg += *it;
  avg /= timing.size();

  //return us
  avg /= 1000;

  return avg;
}


void start_memory_test(int num_threads, int test_loop) {
  const size_t MAX_NUM = 1E8;  // memset never slower
  uint64_t base = 10;
  vector<double> memset_times, omp_set_times, memcpy_times, omp_copy_times;

  struct timespec start, stop;
  memset(&start, 0, sizeof(struct timespec));
  memset(&stop, 0, sizeof(struct timespec));

  cout << "--------------------------------------------------" << endl;
  cout << "num_threads=" << num_threads << "\ttest_loop=" << test_loop << endl;
  cout << "--------------------------------------------------" << endl;
  do {
    const size_t test_size = 2 * base;
    memset_times.resize(0);
    omp_set_times.resize(0);
    memcpy_times.resize(0);
    omp_copy_times.resize(0);;

    unique_ptr<float[]> buffer_1(new float[test_size]), buffer_2(new float[test_size]);
    float *src = buffer_1.get(), *dest = buffer_2.get();

    for (size_t x = 0; x < test_loop; ++x) {
      // Init memory with different values
      memset(src, 3, test_size * sizeof(float));
      memset(dest, 255, test_size * sizeof(float));  // wipe out some/all of src cache

      // memset
      clock_gettime(CLOCK_REALTIME, &start);
      memset(src, 0, test_size * sizeof(float));
      clock_gettime(CLOCK_REALTIME, &stop);
      const double memset_time = (stop.tv_sec - start.tv_sec) * 1000000000 + (stop.tv_nsec -start.tv_nsec);

      clock_gettime(CLOCK_REALTIME, &start);
      #pragma omp parallel for num_threads(num_threads)
      for (int i = 0; i < static_cast<int>(test_size); ++i) {
        src[i] = 42.0f;
      }
      clock_gettime(CLOCK_REALTIME, &stop);
      const double omp_set_time = (stop.tv_sec - start.tv_sec) * 1000000000 + (stop.tv_nsec -start.tv_nsec);

      clock_gettime(CLOCK_REALTIME, &start);
      memcpy(dest, src, test_size * sizeof(float));
      clock_gettime(CLOCK_REALTIME, &stop);
      const double memcpy_time = (stop.tv_sec - start.tv_sec) * 1000000000 + (stop.tv_nsec -start.tv_nsec);

       // bounce the cache and dirty logic
      memset(src, 6, test_size * sizeof(float));
      memset(dest, 200, test_size * sizeof(float));

      clock_gettime(CLOCK_REALTIME, &start);
      #pragma omp parallel for num_threads(num_threads)
      for (int i = 0; i < static_cast<int>(test_size); ++i) {
        dest[i] = src[i];
      }
      clock_gettime(CLOCK_REALTIME, &stop);
      const double omp_copy_time = (stop.tv_sec - start.tv_sec) * 1000000000 + (stop.tv_nsec -start.tv_nsec);

      memset_times.push_back(memset_time);
      omp_set_times.push_back(omp_set_time);
      memcpy_times.push_back(memcpy_time);
      omp_copy_times.push_back(omp_copy_time);
    }

    auto avg_memset_times = average(memset_times);
    auto avg_omp_set_times = average(omp_set_times);
    auto avg_memcpy_times = average(memcpy_times);
    auto avg_omp_copy_times = average(omp_copy_times);
    auto memset_slower = avg_memset_times > avg_omp_set_times;
    auto memcpy_slower = avg_memcpy_times > avg_omp_copy_times;
    auto ompset_memset_ratio = avg_memset_times / avg_omp_set_times;
    auto ompcopy_memcpy_ratio = avg_memcpy_times / avg_omp_copy_times;

    streamsize ss = cout.precision();
    cout << "omp " << setw(6) << left << num_threads 
         << "size " << setw(12) << left << test_size
         << "memset_t(us) " << setw(15) << left << avg_memset_times
         << "omp_set_t(us) " << setw(15) << left << avg_omp_set_times
         << "ompset/memset " << setw(10) << left << fixed << setprecision(2) << ompset_memset_ratio;
         //<< "is_memset_slower " << setw(4) << left << (memset_slower? "Y" : "N")
    cout.precision(ss);
    cout << "memcpy_t(us) " << setw(15) << left << avg_memcpy_times
         << "omp_copy_t(us) " << setw(15) << left << avg_omp_copy_times
         << "ompcopy/memcy " << setw(10) << left << fixed << setprecision(2) << ompcopy_memcpy_ratio
         //<< "is_memcpy_slower " << setw(4) << left << (memset_slower? "Y" : "N")
         << endl;
    cout.precision(ss);

    base *= 10;
  } while (base <= MAX_NUM);
}


int main(int argc, char *argv[]) {
  int num_threads = omp_get_max_threads();
  int test_loop = 10;
  if (argc == 2) {
    num_threads = atoi(argv[1]);
  } else if (argc == 3) {
    num_threads = atoi(argv[1]);
    test_loop =  atoi(argv[2]);
  }
    
  start_memory_test(num_threads, test_loop);

  return (0);
}
