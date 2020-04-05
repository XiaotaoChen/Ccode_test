#include <cstdio>
#include <thread>                // std::thread
#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable
#include "./producer_consumer.h"
// #include "./simple_example.h"
#include "./thread_safe_queue.h"


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

// void test_thread_safe_queue() {
// 	safe_queue::ThreadSafeQueue<int> q;
// 	std::thread consumer([&q]() {
// 		while (true)
// 		{
// 			int i ;
//             q.WaitAndPop(i);
//             printf("consumer %x get %d from threadSafeQueue\n", std::this_thread::get_id(), i);
// 			if (i == 0)
// 			{
// 				break;
// 			}
// 		}
// 	});
// 	q.Push(1);
// 	q.Push(2);
// 	q.Push(3);
// 	q.Push(4);
// 	std::thread producer([&q]() {
// 		for (int i = 10; i >= 0; i--)
// 		{
// 			q.Push(i);
//             printf("producer %x push %d from ThreadSafeQueue\n", std::this_thread::get_id(), i);
// 		}
// 	});
// 	producer.join();
// 	consumer.join();

// }


int main()
{
    // test_simple_example();
    // test_oneproducer_oneconsumer();
    test_thread_safe_queue();



    return 0;
}