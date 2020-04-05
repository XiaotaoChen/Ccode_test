#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

namespace producer_consumer
{

struct ItemReposity{
    int* item_buffer;
    size_t buffer_size;
    size_t read_position;
    size_t write_position;
    std::mutex mtx;
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
    // for multip consumer
    size_t consumer_count = 0;
    std::mutex consumer_mtx;
    // for multip producer
    size_t producer_count = 0;
    std::mutex producer_mtx;
    ItemReposity():buffer_size(5), read_position(0),write_position(0){
        item_buffer = new int[5];
    }
    ItemReposity(int size):buffer_size(size), read_position(0),write_position(0){
        item_buffer = new int[size];
    }
    ~ItemReposity() {
        delete[] item_buffer;
    }
} repo;

// 生产者写入buffer, 先得到buffer的锁，然后判断队列是否为满，
// 当满时则释放mtx, 阻塞直到buffer不为空. 注意判断条件写在while里而不是if，是为了保证当前线程
// 被notify的时候buffer不为满,防止buffer满的情况下，由于其他情况被notify.
// 本例应该可以使用if, 因为只有consumer/producer的notify是分离的．
void produceItem(int item) {
    std::unique_lock<std::mutex> lck(repo.mtx);
    // if((repo.write_position+1)%repo.buffer_size == repo.read_position) {
    // while ((repo.write_position+1)%repo.buffer_size == repo.read_position) {
    //     repo.repo_not_full.wait(lck);
    // }
    repo.repo_not_full.wait(lck, []{ return (repo.write_position+1)%repo.buffer_size != repo.read_position;});
    repo.item_buffer[repo.write_position] = item;
    repo.write_position = (repo.write_position+1) % repo.buffer_size;
    repo.repo_not_empty.notify_one();
    lck.unlock();
}

int consumeItem() {
    std::unique_lock<std::mutex> lck(repo.mtx);
    // if(repo.read_position == repo.write_position) {
    // while (repo.read_position == repo.write_position) {
    //     repo.repo_not_empty.wait(lck);
    // }
    repo.repo_not_empty.wait(lck, []{return repo.read_position != repo.write_position;});
    int val = repo.item_buffer[repo.read_position];
    repo.read_position = (repo.read_position+1) % repo.buffer_size;
    repo.repo_not_full.notify_one();
    lck.unlock();
    return val;
}

void produceTask(int thread_id, int count) {
    for (int i=0; i<count; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        printf("producer %d: %d\n", thread_id, i);
        produceItem(i);
    }
}

void produceMultipTask(int thread_id, int count) {
    bool ready_to_exit = false;
    while(!ready_to_exit) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::unique_lock<std::mutex> lck(repo.producer_mtx);
        if (repo.producer_count<count) {
            produceItem(repo.producer_count);
            printf("producer %d: %d\n", thread_id, repo.producer_count);
            repo.producer_count++;
        }
        else {
            ready_to_exit = true;
            printf("producer %d is to exit!\n", thread_id);
        }
        lck.unlock();
    }
}

void consumeTask(int thread_id, int count) {
    for (int i=0; i<count; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        int val = consumeItem();
        printf("consumer %d %d: %d ...\n", thread_id, i, val);
    }
}

void consumeMultipTask(int thread_id, int count) {
    bool ready_to_exit = false;
    int val=-1;
    while(!ready_to_exit) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::unique_lock<std::mutex> lck(repo.consumer_mtx);
        if (repo.consumer_count < count) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            val = consumeItem();
            printf("consumer %d %d: %d ...\n", thread_id, repo.consumer_count, val);
            repo.consumer_count++;
        }
        else {
            ready_to_exit = true;
            printf("consumer %d ready to exit\n", thread_id);
        }
        lck.unlock();
    }
}


} // namespace producer_consumer
