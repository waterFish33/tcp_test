#pragma once
#include <functional>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "comm.hpp"
using namespace std;
class Task{
    public:
    Task(int fd):_fd(fd){

    }
   Task(){}
    void server(int tmp)
    {

      
            char buf[BUFSIZE] = {0};
            int size = read(tmp, buf, sizeof(buf) - 1);
            if (size > 0)
            {
                buf[size] = '\0';
                cout << "fd" << tmp << ":" << buf;
                write(tmp, buf, strlen(buf));
            }
           
                close(tmp);
                
            
        
    }
    void operator()(){
        server(_fd);
    }
   
    private:
    int _fd;
};