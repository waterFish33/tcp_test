
#include "comm.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
class tcp_client
{
public:
    tcp_client(char *ip, uint16_t port):des_ip(ip),des_port(port)
    {
        
    }
    void Init(){
            std::string serverip = des_ip;
    uint16_t serverport = des_port;
        _sockfd = socket(AF_INET, SOCK_STREAM, 0);
        _addr.sin_family=AF_INET;
        _addr.sin_port=htons(des_port);
        _addr.sin_addr.s_addr=(inet_addr(des_ip));
    // inet_pton(AF_INET, serverip.c_str(), &_addr.sin_addr); // 1. 字符串ip->4字节IP 2. 网络序列

    }
    void Start()
    {
        if (connect(_sockfd,(struct sockaddr*)&_addr,sizeof(_addr)) != 0)
        {
            perror("connect fail!");
            exit(1);
        }
        cout<<"connect server success"<<endl;
        while (1)
        {
            cout<<"please enter: ";
            char buf[BUFSIZE];
            fgets(buf, sizeof(buf), stdin);
            // cout<<"my fgets:"<<buf;
            int n=write(_sockfd, buf, strlen(buf));
            if(n>0){
                 int size = read(_sockfd, buf, sizeof(buf));
            if (size > 0)
            {
                cout << "server:" << buf ;
            }
            }else{
                break;
            }
           
        }
    }
    ~tcp_client()
    {
    }

private:
    char *des_ip;
    uint16_t des_port;
    sockaddr_in _addr;
  
    int _sockfd;
};