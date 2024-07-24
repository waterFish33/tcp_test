#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

class mysocket
{
public:
    mysocket(int socketfd,sockaddr_in addr) : _socketfd(socketfd),_addr(addr)
    {
       
    }
    int Listen(){
        return listen(_socketfd,5);
    }
    int Accept(){
        socklen_t len =sizeof(_addr);
        // int opt =1;
        // setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt));
        return accept(_socketfd,(struct sockaddr*)&_addr,&len);

    }
    int Connect(){
        return connect(_socketfd,(struct sockaddr*)&_addr,sizeof(_addr));
    }
    void Sendto(){

    }
    void Recv(){

    }
    int Bind(){
        return bind(_socketfd,(struct sockaddr*)&_addr,sizeof(_addr));
    }
    ~mysocket() {}

private:
    int _socketfd;
    sockaddr_in _addr;

};