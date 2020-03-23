#pragma once
#include <string>

typedef struct MSG
{
	int code;
	char msg[1024];
}msg, *pmgs;

class echo_client
{
public:
	echo_client(const char* ip,int port);
	~echo_client();

public:
	int client_connect();
	int writed(const char* data);
	void handle_connection();

private:
	int handle_recv_msg(msg data);

private:
	std::string  m_ip;
	int m_port;
	int m_sockfd;
	char recvline[1024];
	fd_set readfds;
};

