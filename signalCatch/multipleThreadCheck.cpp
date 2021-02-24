#include <iostream>
#include <map>
#include <string>
#include <thread>


enum dtypes {_uint8, _int32, _float,};

static std::map<std::string, dtypes> dtype_map = {
    {"uint8", _uint8},
    {"int", _int32},
    {"float", _float},
};

bool ready = false;

void visitMap(int threadIdx) {
    while(!ready) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    for (const auto& item: dtype_map) {
        std::cout << "thread " << threadIdx << ", " << item.first << ": " << item.second << std::endl;
    }
}

int main() {
    int num_threads = 4;
    std::thread threads[num_threads];
    for (int i=0; i<num_threads; i++) {
        threads[i] = std::thread(visitMap, i);
    }
    
    ready = true;
    for (auto & th: threads) {
        th.join();
    }

    return 0;
}

