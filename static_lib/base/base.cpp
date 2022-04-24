#include "base.h"

worker::worker(const Config& config) : mConfig(config) {}
void worker::showInfo() {
  printf("worker info: name: %s, skillCount: %d\n", mConfig.name.c_str(),
         mConfig.skillCount);
  //   printf("worker info: name: %s, skillCount: %d, age: %d\n",
  //          mConfig.name.c_str(), mConfig.skillCount, mConfig.mAge);
}

// int worker::getSkillCount() { return mConfig.skillCount; }
std::string worker::getName() { return mConfig.name; }
// int worker::getSkillCount() { return mConfig.skillCount; }