#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdio>

namespace safe_queue
{

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cond;
    // ensure consumer exit normally
    int total_count = 0;
    std::mutex consumer_mtx;

public:
    ThreadSafeQueue():total_count(10){}
    ThreadSafeQueue(int total_count): total_count(total_count){}
    ThreadSafeQueue(const ThreadSafeQueue& other) {
        std::unique_lock<std::mutex> lck(mtx);
        q = other.q;
        total_count = other.total_count;
        lck.unlock();
    }
    ~ThreadSafeQueue(){}

    void Push(T&& t) {
        std::lock_guard<std::mutex> lck(mtx);
        // std::unique_lock<std::mutex>  lck(mtx);
        q.push(std::move(t));
        cond.notify_one();
        // lck.unlock();
    }
    
    void Push(const T& t) {
        std::lock_guard<std::mutex> lck(mtx);
        // std::unique_lock<std::mutex>  lck(mtx);
        q.push(t);
        cond.notify_one();
        // lck.unlock();
    }

    void WaitAndPop(T& t) {
        std::unique_lock<std::mutex> lck(mtx);
        // cond.wait(lck, []{return !q.empty();});
        while(q.empty()) {
            cond.wait(lck); // only unique_lock can be passed to condition variable
        }
        t = std::move(q.front());; q.pop();
        decrease_consumer_count();
        lck.unlock();
    }

    bool TryPop(T& t) {
        std::lock_guard<std::mutex> lck(mtx);
        // std::unique_lock<std::mutex> lck(mtx);
        if (q.empty()) return false;
        t = std::move(q.front()); q.pop();
        decrease_consumer_count();
        return true;
    }
    bool empty() {
        std::lock_guard<std::mutex> lck(mtx);
        // std::unique_lock<std::mutex> lck(mtx);
        return q.empty();
    }

    int get_consumer_count() {
        std::lock_guard<std::mutex> lck(consumer_mtx);
        return total_count;
    }
    void decrease_consumer_count() {
        std::lock_guard<std::mutex> lck(consumer_mtx);
        total_count--;
    }
    bool is_done() {
        std::lock_guard<std::mutex> lck(consumer_mtx);
        return total_count<=0;
    }

};

void consumer_task(ThreadSafeQueue<int>& tsq) {
    bool raedy_to_exit = false;
    while(!tsq.is_done()) {
        int a;
        tsq.WaitAndPop(a);
        printf("consumer %x get %d from threadSafeQueue\n", std::this_thread::get_id(), a);
    }
}

void producer_task(ThreadSafeQueue<int>& tsq, int count) {
    for (int i=0; i<count; i++) {
        tsq.Push(i);
        printf("producer %x push %d from ThreadSafeQueue\n", std::this_thread::get_id(), i);
    }
}

} // namespace safe_queue



#endif
