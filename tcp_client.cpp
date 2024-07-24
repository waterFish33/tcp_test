#include "tcp_client.hpp"
#include <arpa/inet.h>

int main(int argc,char* argv[]){
    if(argc!=3){
        perror("please enter ./tcp_client -ip -port");
        exit(1);
    }
    tcp_client client(argv[1],stoi(argv[2]));
    client.Init();
    client.Start();
    return 0;
}