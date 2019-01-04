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

}  // namespace utils

