#include "echo_server.h"
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

#define SUCCESS			0
#define ERROR_BASE      50000

enum ERROR
{
	OVER_CONNECT = (ERROR_BASE + 1),
	INVALID_CONNECT = (ERROR_BASE + 2)
};




echo_server::echo_server(int max_cli_size)
	:m_cli_size(max_cli_size),
	cli_cnt(0)
{
	std::vector<int> temp(max_cli_size, -1);
	clifds.swap(temp);
}


echo_server::~echo_server()
{
}


int echo_server::create_server_proc(const char* ip, int port)
{
	
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		fprintf(stderr, "create socket fail,erron:%d,reason:%s\n", errno, strerror(errno));
		return -1;
	}

	/*一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。*/
	int reuse = 1;
	if (-1 == setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))) {
		return -1;
	}

	sockaddr_in serveraddr;
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	//inet_pton convert IPv4 and IPv6 addresses from text to binary form
	//inet_ntop convert IPv4 and IPv6 addresses from binary to text form
	inet_pton(AF_INET, ip, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(port);

	if (-1 == bind(fd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr))) {
		fprintf(stderr, "bind  socket fail,erron:%d,reason:%s\n", errno, strerror(errno));
		return -1;
	}

	fprintf(stdout, "%s:%d is listening\n", ip, port);
	listen(fd, 5);
	return fd;
}


void echo_server::handle_client_proc(int srvfd)
{
	struct timeval tv;
	int retval = 0;
	while (true)
	{
		/*每次调用select前都要重新设置文件描述符和时间，因为事件发生后，文件描述符和时间都被内核修改啦*/
		FD_ZERO(&allfds);
		/*添加监听套接字*/
		FD_SET(srvfd, &allfds);
		maxfd = srvfd;

		tv.tv_sec = 30;
		tv.tv_usec = 0;
		/*将有效客户端套接字加入监听序列*/
		for (int clifd : clifds) {
			if (clifd != -1) {
				//fprintf(stdout, "clifd: %d.\n", clifd);
				FD_SET(clifd,&allfds);
			}
			maxfd = std::max(maxfd, clifd);
		}
		/*开始轮询接收处理服务端和客户端套接字*/
		/*select阻塞等待事件发生*/
		/*select可处理socket读写事件和客户端套接字事件*/
		retval = select(maxfd + 1, &allfds, NULL, NULL, &tv);
		if (retval == -1) {
			fprintf(stderr, "select error:%s.\n", strerror(errno));
			return;
		}
		else if (retval == 0) {
			fprintf(stderr, "select is timeout.\n");
			continue;
		}

		if (FD_ISSET(srvfd, &allfds)) {
			/*监听客户端请求*/
			accept_client_proc(srvfd);
		}
		else
		{
			/*接受处理客户端消息*/
			recv_client_msg(&allfds);
		}
	}
}

int echo_server::accept_client_proc(int srvfd)
{
	sockaddr_in cliaddr;
	socklen_t cliaddrlen = sizeof(cliaddr);
	int clifd = -1;
	printf("accpet clint proc is called.\n");
ACCEPT:
	clifd = accept(srvfd, (sockaddr*)&cliaddr, &cliaddrlen);

	if (clifd == -1) {
		if (errno == EINTR) {
			goto ACCEPT;
		}
		else
		{
			fprintf(stderr, "accept fail,error:%s\n", strerror(errno));
			return -1;
		}
	}

	fprintf(stdout,"accept a new client: %s:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
	con_peer[clifd] = std::make_pair<std::string,int>(inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);

	//将新的连接描述符添加到数组中
	int i = 0;
	for (i = 0; i < clifds.size();i++) {
		if (clifds[i] == -1) {
			clifds[i] = clifd;
			//printf("add client %d\n",clifd);
			cli_cnt++;
			break;
		}
		//fprintf(stdout, "clifd = %d\n", clifds[i]);
	}

	if (i == m_cli_size) {
		fprintf(stderr, "too many clients.\n");
		close_peer(clifd, OVER_CONNECT);
		return -1;
	}
}



void echo_server::recv_client_msg(fd_set *readfds)
{
	printf("recv_client_msg si call\n");
	int readbyte = 0;
	char buf[1024] = { 0 };
	for (int i = 0; i < clifds.size(); i++) {
		if (clifds[i] == -1) {
			continue;
		}

		/*判断客户端套接字是否有数据*/
		if (FD_ISSET(clifds[i], &allfds)) {
			readbyte = read(clifds[i],buf,sizeof(buf));
			if (readbyte <= 0) {
				/*n==0表示读取完成，客户都关闭套接字*/
				FD_CLR(clifds[i],&allfds);
				close(clifds[i]);
				cli_cnt--;
				continue;
			}
			handle_client_msg(clifds[i],buf);
		}
	}
}


int echo_server::handle_client_msg(int fd, char *buf)
{
	assert(buf);
	printf("recv buf is :%s\n", buf);
	msg m_msg;
	m_msg.code = SUCCESS;
	memcpy(m_msg.msg, buf, 1024);
	write(fd, &m_msg, sizeof(msg));
	return 0;
}

int echo_server::close_peer(int fd, int err)
{
	printf("close peer connect[%s:%d]\n", con_peer[fd].first.c_str(),con_peer[fd].second);
	//char buff[128];
	//memcpy(buff,&err,sizeof(err));
	//int error = htons(err);
	msg m_msg;
	m_msg.code = err;
	memcpy(m_msg.msg, "connect over limited!", 1024);
	//write(fd,(const void*)&err,sizeof(err));
	write(fd, (const void*)&m_msg, sizeof(msg));
	return 0;
}

