#include <cstdio>
#include <thread>                // std::thread
#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable
#include "./producer_consumer.h"
#include "./simple_example.h"
#include "./thread_safe_queue.h"
#include "./threadpool.h"


std::mutex mtx; // 全局互斥锁.
std::condition_variable cv; // 全局条件变量.
bool ready = false; // 全局标志位.
void do_print_id(int id)
{
    std::unique_lock <std::mutex> lck(mtx);
    while (!ready) // 如果标志位不为 true, 则等待...
        cv.wait(lck); // 当前线程被阻塞, 同时释放锁，等到cv唤醒该进程后再继续执行，这两行代码相当于cv.wait(lck, ready);
    printf("thread %d\n", id);
}
void go()
{
    std::unique_lock <std::mutex> lck(mtx);
    ready = true; // 设置全局标志位为 true.
    cv.notify_all(); // 唤醒所有线程.
}

void test_simple_example() {

    int num_threads = 10;
    std::thread threads[num_threads];
    for (int i=0; i<num_threads; i++) {
        threads[i] = std::thread(do_print_id, i);
    }
    go();
    for (auto & th: threads) {
        th.join();
    }
    return;
    
}


/**
 * 多生产者－多消费者模型．一般一个互斥变量就对应着一个mutex,
 * 如buffer, produer/consumer互斥访问，需要mtx;
 * 多生产者情况下，要记录当前生产的个数，prducers之间互斥访问，则要producer_mtx
 * 多消费者情况下，要记录当前消费的个数，consumers之间互斥访问，则要consumer_mtx
 * 两个条件变量，分别判断队列是否为空，为满．
*/
void test_oneproducer_oneconsumer() {
    int producer_count = 20;
    int producer_nums = 2;
    int consumer_nums = 2;
    std::thread producers[producer_nums];
    std::thread consumers[consumer_nums];
    for (int i=0; i<producer_nums; i++) {
        // producers[i] = std::thread(producer_consumer::produceTask, i, 20/producer_nums);
        producers[i] = std::thread(producer_consumer::produceMultipTask, i, 20);
    }
    for (int i=0; i<consumer_nums; i++) {
        // consumers[i] = std::thread(producer_consumer::consumeTask, i, 20/consumer_nums);
        consumers[i] = std::thread(producer_consumer::consumeMultipTask, i, 20);
    }
    for (int i=0; i<producer_nums; i++) producers[i].join();
    for (int i=0; i<consumer_nums; i++) consumers[i].join();
}

/**
 * 线程安全的队列.
 * 1. thread safe queue必须使用std::ref(tsq)进行传参，要不然会报错
 * 2. std::lock_guard在创建时就加锁，直到其生命周期结束，std::unique_lock则可以自己设置lock, unlock
*/


void test_thread_safe_queue() {
    int producer_count = 20;
    safe_queue::ThreadSafeQueue<int> tsq = safe_queue::ThreadSafeQueue<int>(producer_count);

    int producer_nums = 2;
    int consumer_nums = 2;
    std::thread producers[producer_nums];
    std::thread consumers[consumer_nums];

    for (int i=0; i<producer_nums; i++) {
        producers[i] = std::thread(safe_queue::producer_task, std::ref(tsq), producer_count/producer_nums);
    }

    for (int i=0; i<consumer_nums; i++) {
        consumers[i] = std::thread(safe_queue::consumer_task, std::ref(tsq));
    }

    for (int i=0; i<producer_nums; i++) producers[i].join();
    for (int i=0; i<consumer_nums; i++) consumers[i].join();
}

/**
 * 线程池的实现，需要有一个存放任务的 thread safe queue, 单独实现的话会多使用互斥量，因为thread pool中的conditional vairable需要一个互斥量q_mtx, 
 * 而safequeue中也有一个互斥量，这两个互斥量其实是相同的，　故不单独实现safequeue,和少使用一个互斥量
*/
void test_threadpool() {
    thread_pool::ThreadPool pool(3);
    pool.init();
    for (int i=1; i<4; i++) {
        for (int j=1; j<10; j++) {
            pool.submit(thread_pool::multiply, i, j);
        }
    }
    int output_ref;
    auto future1 = pool.submit(thread_pool::multiply_output, std::ref(output_ref), 5, 6);
    future1.get(); // wait unitl output is finish
    printf("Last operation result is equals to %d\n", output_ref);

    auto future2 = pool.submit(thread_pool::multiply_return, 5, 3);
    int res = future2.get();
    printf("Last operation result is equals to %d\n", res);

    pool.shutdown();
}

void test_mulitpthread() {
    int producer_num = 4;
    int consumer_num = 1;
    std::thread producers[producer_num];
    std::thread consumers[consumer_num];
    for (int i=0; i<producer_num; i++) {
        producers[i] = std::thread(multip_thread::producer, i);
    }
    for (int i=0; i<consumer_num; i++) {
        consumers[i] = std::thread(multip_thread::consumer, i, producer_num);
    }

    for (int i=0; i<producer_num; i++) producers[i].join();
    for (int i=2; i<consumer_num; i++) consumers[i].join();
}


int main()
{
    // test_simple_example();
    // test_oneproducer_oneconsumer();
    // test_thread_safe_queue();
    // test_threadpool();
    test_mulitpthread();



    return 0;
}