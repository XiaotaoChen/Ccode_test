#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
void f()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
int main()
{
    auto t1 = std::chrono::steady_clock::now();
    f();
    auto t2 = std::chrono::steady_clock::now();
    auto ts = t2 - t1;
    auto ts_micros = std::chrono::duration_cast<std::chrono::microseconds>(ts).count();
    std::cout<<"ts_micros: "<<ts_micros<<std::endl;
}
