#pragma once

#include <iostream>
#include <pthread.h>
#include <functional>
#include <string>
using fun_t = std::function<void *(void *)>;
class Thread
{
private:
    pthread_t _tid;
    fun_t _func;
    const std::string _tname;

public:
    Thread(const std::string threadname, fun_t func) : _tid(0), _tname(threadname), _func(func)
    {
    }
    static void *ThreadRoutine(void *args)
      
    {  
        Thread *ts = static_cast<Thread *>(args);
         std::cout<<"ThreadRoutine begin"<<std::endl;
        ts->_func(nullptr);
        return nullptr;
    }
    void Start()
    {
       // std::cout<<"11"<<std::endl;
        pthread_create(&_tid, nullptr, ThreadRoutine, this);
    }
    void Join()
    {
        pthread_join(_tid,nullptr);
    }
    ~Thread() {}
};