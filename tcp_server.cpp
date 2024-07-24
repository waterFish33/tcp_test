#include "tcp_server.hpp"

int main(int argc,char* argv[]){
    if(argc!=2){
        perror("please enter ./tcp_server -port");
        exit(1);
    }
    tcp_server server(atoi(argv[1]));
    server.Init();
    server.Start();
    
    return 0;
}