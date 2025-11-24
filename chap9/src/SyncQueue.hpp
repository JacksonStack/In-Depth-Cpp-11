//
// Created by Kylin on 2024/9/2.
//
#ifndef SYNCQUEUE_HPP_
#define SYNCQUEUE_HPP_

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

using namespace std;

/**
 * 同步队列类模板定义
 * 该类实现了一个线程安全的同步队列，使用条件变量和互斥量来同步多线程间的生产者和消费者问题
 * 模板参数T表示队列中元素的类型
 */
template <typename T>
class SyncQueue {
public:
    /**
     * 构造函数
     * @param maxSize 队列的最大大小
     */
    SyncQueue(int maxSize) : m_maxSize(maxSize), m_needStop(false) {}

    /**
     * 向队列中放入元素的重载函数
     * @param x 要放入队列的元素
     */
    void Put(const T& x) {
        Add(x);
    }

    /**
     * 向队列中放入元素的重载函数，使用右值引用
     * @param x 要放入队列的元素
     */
    void Put(T&& x) {
        Add(std::forward<T>(x));
    }

    /**
     * 从队列中取出所有元素
     * @param list 用于存储取出的队列中所有元素的列表
     */
    void Take(std::list<T>& list) {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] { return NotEmpty() || m_needStop; });

        if (m_needStop)
            return;
        list = std::move(m_queue);
        m_notFull.notify_one();
    }

    /**
     * 从队列中取出一个元素
     * @param x 用于存储取出的队列元素的引用
     */
    void Take(T& x) {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] { return NotEmpty() || m_needStop; });

        if (m_needStop)
            return;
        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

    /**
     * 停止队列操作
     * 该函数确保所有等待的线程都被唤醒
     */
    void Stop() {
        {
            std::lock_guard<std::mutex> locker(m_mutex);
            m_needStop = true;
        }
        m_notFull.notify_all();
        m_notEmpty.notify_all();
    }

    /**
     * 检查队列是否为空
     * @return 队列是否为空的布尔值
     */
    bool Empty() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    /**
     * 检查队列是否已满
     * @return 队列是否已满的布尔值
     */
    bool Full() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size() == m_maxSize;
    }

    /**
     * 获取队列当前的大小
     * @return 队列当前的大小
     */
    size_t Size() {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

    /**
     * 获取队列当前的元素数量
     * @return 队列当前的元素数量
     */
    int Count() {
        return m_queue.size();
    }
private:
    /**
     * 检查队列是否未满的辅助函数
     * @return 队列是否未满的布尔值
     */
    bool NotFull() const {
        bool isFull = m_queue.size() >= m_maxSize;
        if (isFull)
            cout << "buffer is full, need to wait" << endl;
        return !isFull;
    }

    /**
     * 检查队列是否非空的辅助函数
     * @return 队列是否非空的布尔值
     */
    bool NotEmpty() const {
        bool isEmpty = m_queue.empty();
        if (isEmpty)
            cout << "buffer is empty, need to wait ... async thread id" << this_thread::get_id() << endl;
        return !isEmpty;
    }

    /**
     * 向队列中添加元素的模板函数
     * @param x 要添加到队列的元素
     */
    template<class F>
    void Add(F&& x) {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notFull.wait(locker, [this] { return NotFull() || m_needStop; });
        if (m_needStop)
            return;
        m_queue.push_back(std::forward<F>(x));
        m_notEmpty.notify_one();
    }
private:
    std::list<T> m_queue;                       // 缓冲区
    std::mutex m_mutex;                         // 互斥量和条件变量
    std::condition_variable m_notEmpty;         // 非空条件变量
    std::condition_variable m_notFull;          // 非满条件变量
    int m_maxSize;                              // 同步队列最大长度
    bool m_needStop;                            // 停止标志
};

#endif // SYNCQUEUE_HPP_
