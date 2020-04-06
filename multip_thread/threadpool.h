#ifndef THREAD_POOL_
#define THREAD_POOL_

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <future>
#include <memory>
#include <chrono>
#include <cstdio>

namespace thread_pool
{

template<typename T>
class SafeQueue
{
private:
    std::queue<T> q;
    std::mutex mtx;
public:
    SafeQueue(){}
    ~SafeQueue(){}
    void enqueue(const T& t) {
        // std::unique_lock<std::mutex> lck(mtx);
        std::lock_guard<std::mutex> lck(mtx);
        q.emplace(t);
    }
    bool dequeue(T& t) {
        // std::unique_lock<std::mutex> lck(mtx);
        std::lock_guard<std::mutex> lck(mtx);
        if (q.empty()) return false;
        t = std::move(q.front()); q.pop();
        return true;
    }

    bool empty() {
        // std::unique_lock<std::mutex> lck(mtx);
        std::lock_guard<std::mutex> lck(mtx);
        return q.empty();
    }

    int size() {
        std::lock_guard<std::mutex> lck(mtx);
        return q.size();
    }
};

class ThreadPool
{
private:
    class ThreadWorker {
        private:
            int thread_id;
            ThreadPool* pool;
        public:
            ThreadWorker(ThreadPool* pool, int id): pool(pool), thread_id(id){}
            void operator()() {
                std::function<void()> func;
                bool has_task = false;
                while(!pool->is_shutdown) {
                    std::unique_lock<std::mutex> lck(pool->q_mtx);
                    // if (pool->m_queue.empty()) {
                    //     pool->cv.wait(lck);
                    // }
                    // has_task = pool->m_queue.dequeue(func);
                    // lck.unlock();
                    // if (has_task) {
                    //     printf("thread %d to run task...\n", thread_id);
                    //     func();
                    // }
                    pool->cv.wait(lck, [this]{return pool->is_shutdown||!pool->m_queue.empty();});
                    if (pool->is_shutdown) break;
                    func = std::move(pool->m_queue.front()); pool->m_queue.pop();
                    lck.unlock();
                    printf("thread %d to run task...\n", thread_id);
                    func();
                }
            }
    };

    std::vector<std::thread> threads;
    bool is_shutdown;
    using Task = std::function<void()>;
    // SafeQueue<Task> m_queue;
    std::queue<Task> m_queue;
    std::mutex q_mtx;
    std::condition_variable cv;

public:
    ThreadPool(){}
    ~ThreadPool(){}
    ThreadPool(const int n_threads): threads(std::vector<std::thread>(n_threads)), is_shutdown(false) {

    }
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    void init() {
        for (int i=0; i<threads.size(); i++) {
            threads[i] = std::thread(ThreadWorker(this, i));
        }
    }

    void shutdown() {
        // while (!m_queue.empty()) {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // }

        while(1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::lock_guard<std::mutex> lck(q_mtx);
            if (m_queue.empty()) break;
        }

        is_shutdown = true;
        cv.notify_all();
        for (int i=0; i<threads.size(); i++) {
            if (threads[i].joinable()) threads[i].join();
        }
    }

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        std::function<void()> wrapper_func = [task_ptr]() {
            (*task_ptr)();
        };
        // m_queue.enqueue(wrapper_func);
        // cv.notify_one();

        std::unique_lock<std::mutex> lck(q_mtx);
        m_queue.emplace(wrapper_func);
        cv.notify_one();
        lck.unlock();
        return task_ptr->get_future();
    }

};


void multiply(const int a, const int b) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100+std::rand()%1000));
    const int res = a * b;
    printf("%d * %d = %d\n", a, b, res);
}

// Same as before but now we have an output parameter
void multiply_output(int & out, const int a, const int b) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100+std::rand()%1000));
  out = a * b;
  printf("%d * %d = %d\n", a, b, out);
}

// Same as before but now we have an output parameter
int multiply_return(const int a, const int b) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100+std::rand()%1000));
  const int res = a * b;
  printf("%d * %d = %d\n", a, b, res);
  return res;
}

} // namespace thread_pool


#endif