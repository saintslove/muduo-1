#include <iostream>
#include <atomic>
#include "boost/smart_ptr.hpp"
#include "muduo/base/AsyncLogging.h"

using namespace std;
#define A 50

int main(int argc, char *argv[])
{
	std:atomic<int> m_atomic(1);
	m_atomic.fetch_add(1);
	char sz[] = "Hello, World!";	//Hover mouse over "sz" while debugging to see its contents
	cout << sz << endl;	//<================= Put a breakpoint here
	cout << "m_atomic = " << m_atomic << endl;
	cout << A << endl;
	return 0;
}