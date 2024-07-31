#include "comm.hpp"
#include "ThreadPool.hpp"
#include "Task.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <cstring>
#define LISFDNUMS 5
using namespace std;
class tcp_server
{
public:
    tcp_server(uint16_t port) : _port(port)
    {
    }
    void Init()
    {
        _listenfd = socket(AF_INET, SOCK_STREAM, 0);
        // int opt=1;
        // setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt));

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        _addr.sin_addr.s_addr = htonl(INADDR_ANY);
        threadpool = ThreadPool<Task>::GetInstance();
        threadpool->Start();
        maxfd=3;
    }
    void server(int tmp)
    {

        cout << "accept :" << tmp << endl;
        while (1)
        {

            char buf[BUFSIZE] = {0};
            int size = read(tmp, buf, sizeof(buf) - 1);
            if (size > 0)
            {
                buf[size] = '\0';
                cout << "fd" << tmp << ":" << buf;
                write(tmp, buf, strlen(buf));
            }
            else if (size == 0)
            {

                cout << "client close" << endl;
                if(tmp==maxfd){
                    maxfd--;
                }
                close(tmp);
                break;
            }
            else
            {
                cout << "other" << endl;
                if(tmp==maxfd){
                    maxfd--;
                }
                close(tmp);
                break;
            }
        }
    }
    void Start()
    {
        bind(_listenfd, (struct sockaddr *)&_addr, sizeof(_addr));
        cout << "bind" << endl;
        listen(_listenfd, LISFDNUMS);
        cout << "listen" << endl;
        while (1)
        {
            sockaddr_in temp;
            socklen_t len = sizeof(temp);
            int tmp = accept(_listenfd, (struct sockaddr *)&temp, &len);
             cout << "accept :" << tmp << endl;

        
            
                threadpool->Push(Task(tmp));
                //sleep(1);
            
            // sleep(1);
        }
    }
    ~tcp_server()
    {
        close(_listenfd);
    }

private:
    
    uint16_t _port;
    sockaddr_in _addr;
    int _listenfd;
    ThreadPool<Task> *threadpool;
};