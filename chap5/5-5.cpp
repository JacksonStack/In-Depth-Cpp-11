#include <mutex>
#include <thread>
#include <condition_variable>

template <typename T>
class SyncQueue {
    bool IsFull() const {
        return m.queue
    } 



private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable_any m_notEmpty;
    std::condition_variable_any m_notNotFull;
    int m_maxSize
};