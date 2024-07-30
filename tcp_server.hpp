#include "comm.hpp"
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
    }
    void server(int tmp){
       
        cout << "accept :" << tmp << endl;
        while (1)
        {

            char buf[BUFSIZE] = {0};
            int size = read(tmp, buf, sizeof(buf) - 1);
            if (size > 0)
            {
                buf[size] = '\0';
                cout << "fd" << tmp << ":" << buf ;
                write(tmp, buf, strlen(buf));
            }
            else if (size == 0)
            {

                cout << "client close" << endl;
                close(tmp);
                break;
            }
            else
            {
                cout << "other" << endl;
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
        while(1){
             sockaddr_in temp;
             socklen_t len = sizeof(temp);
            int tmp = accept(_listenfd, (struct sockaddr *)&temp, &len);
            if(tmp>0){
                pid_t pid=fork();
                if(pid==0){
                    server(tmp);

                }
            }
            sleep(1);
        }

    }
    ~tcp_server()
    {
    }

private:
    uint16_t _port;
    sockaddr_in _addr;
    int _listenfd;
};