#include <iostream>
#include "server_epoll.h"
#include <array>

using namespace std;

#if __cplusplus >= 201103L
#include <random>
//std::cout << __cplusplus << std::endl;
#else
//std::cout << __cplusplus << std::endl;
#endif 

int main(int argc, char *argv[])
{
	std::cout << __cplusplus << std::endl;
	server_epoll epoll(100,10);
	int sockfd = epoll.initSocket("127.0.0.1", 8787);
	//单进程单线程结合io multiplexing
	epoll.do_epoll(sockfd);
	return 0;
}