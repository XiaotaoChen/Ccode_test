#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable
#include <cstdio>
#include <queue>
#include <iostream>

namespace multip_thread
{

class go_trace {
public:
    go_trace(){}
    ~go_trace(){}
    void do_print_id()
    {
        std::unique_lock <std::mutex> lck(mtx);
        while (!ready) // 如果标志位不为 true, 则等待...
            cv.wait(lck); // 当前线程被阻塞, 同时释放锁，等到cv唤醒该进程后再继续执行，这两行代码相当于cv.wait(lck, ready);
        printf("thread %d\n", 0);
    }
    void go()
    {
        std::unique_lock <std::mutex> lck(mtx);
        ready = true; // 设置全局标志位为 true.
        cv.notify_all(); // 唤醒所有线程.
    }
private:
    std::mutex mtx; // 全局互斥锁.
    std::condition_variable cv; // 全局条件变量.
    bool ready = false; // 全局标志位.
};

std::queue<int> qu;
int size = 4;
std::mutex mtx;
std::condition_variable isempty;
std::condition_variable isfull;
bool shutdown = false;
std::mutex producer_mtx;
int producer_done = 0;

void producer(int thread_id) {
    int i = 0;
    while(!shutdown) {
        std::unique_lock<std::mutex> lck(mtx);
        while (qu.size() == size) {
            isempty.wait(lck);
        }
        std::cout << "producer " << thread_id << " to produce " << i \
                  << " qu.size: " << qu.size() << " ...\n";
        qu.push(i++);
        isfull.notify_one();
    }
    std::lock_guard<std::mutex> lg(producer_mtx);
    producer_done++;
    std::cout << "producer " << thread_id << " to shutdown...\n";
}

void consumer(int thread_id, int producer_count) {
    while(producer_done < producer_count) {
        std::unique_lock<std::mutex> lck(mtx);
        while (qu.empty()) {
            isfull.wait(lck);
        }
        int val = qu.front(); qu.pop();
        std::cout << "consumer " << thread_id << " consume " << val << std::endl;
        if (val >=10) shutdown = true;
        isempty.notify_one();
    }
    std::cout << "consumer" << thread_id << " is shutdown...\n";
}


} // namespace multip_thread
