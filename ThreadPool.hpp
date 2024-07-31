#pragma once

#include "Thread.hpp"
#include "LockGuard.hpp"
#include <string>
#include <queue>
#include <vector>

#define DEFAULTNUMS 5

template <class T>
class ThreadPool
{

private:
    // Thread _thread;
    std::queue<T> _q;
    std::vector<Thread> _vt;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;

    static ThreadPool<T> *instance;
    ThreadPool()
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond, nullptr);
        for (int i = 1; i <= DEFAULTNUMS; i++)
        {
            std::string threadname = "thread_";
            threadname += std::to_string(i);
            _vt.emplace_back(threadname, std::bind(&ThreadPool<T>::ThreadRun, this, nullptr));
        }
    }
    ThreadPool(ThreadPool<T> &) = delete;
    const ThreadPool<T> &operator=(const ThreadPool<T>) = delete;

public:
    static ThreadPool<T> *GetInstance()
    {
        // LockGuard lockguard(&_mutex);

        if (instance == nullptr)
        {
            std::cout << "GetInstance" << std::endl;
            instance = new ThreadPool<T>;
        }

        return instance;
    }
    void *ThreadRun(void *args)
    {
                 

        while (true)
        {
            T t;
           // std::cout << "ThreadRun" << std::endl;
            {
                LockGuard lockguard(&_mutex);
                //std::cout << "断点1" << std::endl;
                while (_q.empty())
                {
 //std::cout << "断点2" << std::endl;
                    pthread_cond_wait(&_cond, &_mutex);
                     //std::cout << "断点3" << std::endl;
                }
                //std::cout << "断点4" << std::endl;
                t = _q.front();
                _q.pop();
                 
            }
           // std::cout << "11" << std::endl;
            t();
        }
    }
    void Push(T t)
    {
        LockGuard lockguard(&_mutex);
        // std::cout << "Push" << std::endl;
        _q.push(t);
        pthread_cond_signal(&_cond);
    }
    void Start()
    {
        for (auto &thread : _vt)
        {
            // std::cout<<"11"<<std::endl;
            thread.Start();
        }
    }
    void Wait()
    {
        for (auto &thread : _vt)
        {
            thread.Join();
        }
    }
    ~ThreadPool()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }
};

template <class T>
ThreadPool<T> *ThreadPool<T>::instance = nullptr;