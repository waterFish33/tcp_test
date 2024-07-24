.PHONY:all
all:tcp_client tcp_server
tcp_client:tcp_client.cpp
	g++ -o tcp_client tcp_client.cpp -std=c++11
tcp_server:tcp_server.cpp
	g++ -o tcp_server tcp_server.cpp -std=c++11
.PHONY:clean
clean:
	rm -rf tcp_client tcp_server
.PHONY:remake
remake:
	make clean
	make