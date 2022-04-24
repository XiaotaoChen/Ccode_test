#include <string>
#include "pro/pro.h"

int main() {
  std::string name = "cxt";
  int skillCount = 2;
  MeituanWorker inst(name, skillCount);
  inst.showInfo();

  return 0;
}
