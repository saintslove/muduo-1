#pragma once
#include <sys/select.h>
#include <vector>
#include <stdio.h>
#include <map>
#include <utility>
#include <string>

typedef struct MSG
{
	int code;
	char msg[1024];
}msg,*pmgs;

class echo_server
{
public:
	echo_server(int max_cli_size);
	~echo_server();

public:
	int create_server_proc(const char* ip, int port);
	void handle_client_proc(int srvfd);

private:
	int accept_client_proc(int srvfd);
	void recv_client_msg(fd_set *readfds);
	int handle_client_msg(int fd, char *buf);
	int close_peer(int fd,int err);

private:
	int m_cli_size;
	int cli_cnt;  //客户端数量
	std::vector<int> clifds; //客户端文件描述符集合 
	fd_set allfds;   //句柄集合
	int maxfd;  //最大文件描述符
	std::map<int, std::pair<std::string, int> > con_peer;
};

