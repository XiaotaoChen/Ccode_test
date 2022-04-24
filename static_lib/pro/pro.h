
#ifndef PRO_h
#define PRO_h

#include <string>
#include "../base/base.h"

class MeituanWorker {
 private:
  worker* mWorker;

 public:
  MeituanWorker(const std::string& name, int skillCount);
  ~MeituanWorker();
  void showInfo();
};

#endif