#include <iostream>
#include "echo_client.h"

using namespace std;

int main(int argc, char *argv[])
{
	echo_client client("127.0.0.1",8787);
	client.client_connect();
	client.writed("hello world!");
	client.handle_connection();
	return 0;
}