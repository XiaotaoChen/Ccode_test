#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable
#include <cstdio>

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

} // namespace multip_thread
