#include <iostream>
#include "echo_server.h"

using namespace std;


int main(int argc, char *argv[])
{
	echo_server server(2);
	int srvfd = server.create_server_proc("127.0.0.1", 8787);
	if (-1 == srvfd) {
		fprintf(stderr,"socket create or bind fail.\n");
		return -1;
	}
	server.handle_client_proc(srvfd);
	return 0;
}