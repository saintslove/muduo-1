#include "server_epoll.h"
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <boost/function.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <array>

typedef boost::function<void(int fd, int events, void* args)> eventCall;

server_epoll::server_epoll(int fdsize,int eventSize)
	:m_fdsize(fdsize)
	,m_eventSize(eventSize)
{
}


server_epoll::~server_epoll()
{
}

int server_epoll::initSocket(const char* ip,int port)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd <= 0) {
		fprintf(stderr,"create socket fail,erron:%d,reason:%s\n", errno, strerror(errno));
		return -1;
	}
	/*修改文件描述符属性
	F_SETFL 设置对应的访问标志，一般常用来设置做非阻塞读写操作
	O_NONBLOCK 非阻塞读写
	*/
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	struct sockaddr_in sockaddress;
	bzero(&sockaddress,sizeof(sockaddr));
	sockaddress.sin_family = AF_INET;
	sockaddress.sin_port = htons(port);
	inet_pton(AF_INET, ip, &sockaddress.sin_addr);
	if (-1 == bind(sockfd, (const struct sockaddr*)&sockaddress, sizeof(sockaddress)))
	{
		fprintf(stderr, "bind  socket fail,erron:%d,reason:%s\n", errno, strerror(errno));
		return -1;
	}
	fprintf(stdout, "%s:%d is listening\n", ip, port);
	listen(sockfd,5);
	return sockfd;

}

void server_epoll::addEvent(int epollfd,int sockfd, int stat)
{
	struct epoll_event event;
	event.data.fd = sockfd;
	event.events = stat;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &event);
}

void server_epoll::deleteEvent(int epollfd, int sockfd, int stat)
{
	struct epoll_event event;
	event.data.fd = sockfd;
	event.events = stat;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, sockfd, &event);
}


void server_epoll::modifyeEvent(int epollfd, int sockfd, int stat)
{
	struct epoll_event event;
	event.data.fd = sockfd;
	event.events = stat;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, sockfd, &event);
}

/*
	多线程程序，线程大致包括三类：
	1）io线程，主循环选择io multiplexing（多路复用），阻塞等待select/poll/epoll_wait
	事件激活，用于处理（分发）激活事件
	2）计算线程，主线程选择blocking queue,阻塞在condition variable处理任务，一般应用于
	thread pool
	3）第三方库所用线程
*/

int server_epoll::do_epoll(int sockfd)
{
	struct epoll_event events[EPOLLEVENTS];
	//std::vector<epoll_event> events(m_eventSize);
	//std::array<epoll_event, EPOLLEVENTS> events;
	//创建epoll句柄
	int epollfd = epoll_create(m_fdsize);
	//添加监听描述符事件,监听写事件
	addEvent(epollfd, sockfd, EPOLLIN);
	while (true)
	{
		//阻塞等待事件发生 select/poll/epoll_wait
		int epollSize = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
		if (epollSize < 0) {
			fprintf(stderr, "epoll_wait fail,erron:%d,reason:%s\n", errno, strerror(errno));
			continue;
		}
		handle_event(epollfd, epollSize, events, sockfd);
	}
	close(epollfd);
}

void server_epoll::handle_event(int epollfd, int epollSize, epoll_event* events, int sockfd)
{
	int fd = -1;
	//顺序处理每个event
	for (int i = 0; i < epollSize; i++) {
		fd = events[i].data.fd;
		if (fd == sockfd && events[i].events & EPOLLIN) {
			//监听套接字可读事件，有新的连接介入
			handle_accept(epollfd, sockfd);
		}
		else if(events[i].events & EPOLLIN)
		{
			// EPOLLIN事件触发，新连接发生读事件
			do_read(epollfd,fd);
		}
		else if (events[i].events & EPOLLOUT)
		{
			// EPOLLOUT事件触发，新连接发生写事件
			do_write(epollfd, sockfd);
		}
	}
}

void server_epoll::handle_accept(int epollfd,int sockfd)
{
	struct  sockaddr_in peerAddr;
	socklen_t len = sizeof(peerAddr);
	int fd = accept(sockfd,(sockaddr*)&peerAddr,&len);
	if (fd == -1) {
		fprintf(stderr, "accept fail,erron:%d,reason:%s\n", errno, strerror(errno));
		return;
	}
	fprintf(stdout,"accept new client: %s:%d",inet_ntoa(peerAddr.sin_addr),peerAddr.sin_port);
	//将新客户端添加到监控序列
	addEvent(epollfd, fd, EPOLLIN);
}

void server_epoll::do_read(int epollfd,int sockfd)
{
	char buf[1024] = { 0 };
	int readByte = read(sockfd, buf, sizeof(buf));
	if (readByte == -1) {
		fprintf(stderr, "read client,erron:%d,reason:%s\n", errno, strerror(errno));
		close(sockfd);
		deleteEvent(epollfd, sockfd, EPOLLIN);
	}
	else if(readByte == 0)
	{
		fprintf(stderr, "read client close\n");
		close(sockfd);
		deleteEvent(epollfd, sockfd, EPOLLIN);
	}
	else
	{
		fprintf(stdout, "get msg:%s\n",buf);
		//EPOLLOUT事件只有在不可写到可写的转变时刻，才会触发一次，所以叫边缘触发
		//调用epoll_ctl重置event事件（EPOLLOUT）,可强制触发EPOLLOUT事件，即刻触发EPOLLOUT事件
		modifyeEvent(epollfd,sockfd,EPOLLOUT);
	}

}


void server_epoll::do_write(int epollfd, int sockfd)
{
	const char* buf = "hello client!";
	int nwrite = write(sockfd, buf, strlen(buf) + 1);
	if (nwrite == -1)
	{
		fprintf(stderr, "write client,erron:%d,reason:%s\n", errno, strerror(errno));
		close(sockfd);
		deleteEvent(epollfd, sockfd, EPOLLOUT);
	}
	else
	{
		modifyeEvent(epollfd, sockfd, EPOLLIN);
	}
}