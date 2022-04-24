#include "pro.h"

MeituanWorker::MeituanWorker(const std::string& name, int skillCount) {
  Config config;
  config.name = name;
  config.skillCount = skillCount;
  mWorker = new worker(config);
}
MeituanWorker::~MeituanWorker() {
  delete mWorker;
  mWorker = nullptr;
}
void MeituanWorker::showInfo() {
  mWorker->showInfo();
  printf("MeituanWorker's name: %s\n", mWorker->getName().c_str());
}