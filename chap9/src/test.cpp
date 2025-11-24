//
// Created by Kylin on 2024/9/2.
//
#include "threadpool.cpp"

void TestThreadPool() {
    ThreadPool pool;

    std::thread thd1([&pool] {
        for (int i = 0; i < 10; ++i) {
            auto thdId = this_thread::get_id();
            pool.AddTask([thdId] {
                cout << "sync1 thread id: " << thdId << endl;
            });
        }
    });

    std::thread thd2 ([&pool] {
        for (int i = 0; i < 10; ++i) {
            auto thdId = this_thread::get_id();
            pool.AddTask([thdId] {
                cout << "sync2 thread id: " << thdId << endl;
            });
        }
    });

    this_thread::sleep_for(std::chrono::seconds(2));
    getchar();
    pool.Stop();
    thd1.join();
    thd2.join();
}

int main() {
    TestThreadPool();
    return 0;
}