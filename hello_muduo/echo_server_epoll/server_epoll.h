#pragma once
#include <sys/epoll.h>
#include <poll.h>
#include <array>
#include <sstream>

class server_epoll
{
public:
	server_epoll(int fdsize, int eventSize);
	~server_epoll();

	int initSocket(const char* ip, int port);
	int do_epoll(int sockfd);
private:
	void addEvent(int epollfd, int sockfd, int stat);
	void deleteEvent(int epollfd, int sockfd, int stat);
	void modifyeEvent(int epollfd, int sockfd, int stat);
	void handle_event(int epollfd, int epollSize, epoll_event* events, int sockfd);
	void handle_accept(int epollfd, int sockfd);
	void do_read(int epollfd, int sockfd);
	void do_write(int epollfd, int sockfd);
private:
	int m_fdsize;
	int m_eventSize;

	static const int EPOLLEVENTS = 10;
};

