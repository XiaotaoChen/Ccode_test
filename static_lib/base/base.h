#ifndef BASE_h
#define BASE_h

#include <string>

typedef struct _Config {
  std::string name;
  // int mAge = 10;
  int skillCount;
  // int mAge = 10;
} Config;

class worker {
 private:
  Config mConfig;

 public:
  worker(const Config& config);
  void showInfo();
  // int getSkillCount();
  std::string getName();
  // int getSkillCount();
};

#endif