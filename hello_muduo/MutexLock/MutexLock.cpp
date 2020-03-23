#include <iostream>
#include <assert.h>

using namespace std;

class MutexLock
{
public:
	MutexLock()
		:hold_(0)
	{
		pthread_mutex_init(&mutex_, NULL);
	}

	~MutexLock()
	{
		assert(hold_ == 0);
		pthread_mutex_destroy(&mutex_);
	}

	void lock()
	{
		pthread_mutex_lock(&mutex_);
		hold_ = getpid();
	}

	void unlock()
	{
		hold_ = 0;
		pthread_mutex_unlock(&mutex_);
	}
private:
	pid_t hold_;
	pthread_mutex_t mutex_;
};


int main(int argc, char *argv[])
{
	char sz[] = "Hello, World!";	//Hover mouse over "sz" while debugging to see its contents
	cout << sz << endl;	//<================= Put a breakpoint here
	return 0;
}