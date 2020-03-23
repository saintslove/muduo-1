#include "echo_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

echo_client::echo_client(const char* ip, int port)
	:m_ip(ip),
	m_port(port)
{
}


echo_client::~echo_client()
{
}


int echo_client::client_connect()
{
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockfd == -1) {
		fprintf(stderr, "create socket fail,erron:%d,reason:%s\n", errno, strerror(errno));
		return -1;
	}

	sockaddr_in cliaddr;
	cliaddr.sin_family = AF_INET;
	inet_pton(AF_INET, m_ip.c_str(), &cliaddr.sin_addr);
	cliaddr.sin_port = htons(m_port);

	int retval = connect(m_sockfd, (const sockaddr*)&cliaddr, sizeof(cliaddr));
	if (retval < 0) {
		fprintf(stderr,"connect fail,errno:%d error:%s\n",errno,strerror(errno));
		return -1;
	}

}

int echo_client::writed(const char* data)
{
	int nbyte = write(m_sockfd,data,strlen(data) + 1);
	if (nbyte == -1) {
		fprintf(stderr,"send data to server[ip:port] fail!,errno:%d,error:%s\n",m_ip.c_str(),m_port,errno,strerror(errno));
		return -1;
	}
	fprintf(stderr, "send data to server[%s:%d] success!\n", m_ip.c_str(), m_port);
	return nbyte;
}


void echo_client::handle_connection()
{
	//fd_set readfds;

	FD_ZERO(&readfds);
	FD_SET(m_sockfd,&readfds);
	int maxfd = m_sockfd;
	
	timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	int retfd = -1;

	while (true)
	{
		retfd = select(maxfd + 1, &readfds, NULL, NULL, &tv);
		if (retfd == -1) {
			return;
		}
		if (retfd == 0) {
			fprintf(stdout,"timeout!\n");
			continue;
		}

		if (FD_ISSET(m_sockfd, &readfds)) {
			msg m_msg;
			int nbyte = read(m_sockfd,&m_msg,sizeof(msg));
			if (nbyte <= 0) {
				fprintf(stderr,"client: server is closed.\n");
				close(m_sockfd);
				FD_CLR(m_sockfd,&readfds);
				return;
			}
			if (0 != handle_recv_msg(m_msg)) {
				return;
			}
		}
	}
}

int echo_client::handle_recv_msg(msg data)
{
	fprintf(stdout, "client recv msg :%s  code:%d\n", data.msg,data.code);
	if (data.code == 0) {
		write(m_sockfd, data.msg, strlen(data.msg) + 1);
		sleep(5);
	}
	else
	{
		fprintf(stdout, "client closed!\n");
		close(m_sockfd);
		FD_CLR(m_sockfd, &readfds);
	}
	return data.code;
	//int err = 0;
	//memcpy(&err, recvline, sizeof(int));
	//fprintf(stdout, "client errno :%d\n", err);	
}