// static is not thread safe
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
using namespace std;

static int val =0;
//int val =0;
std::mutex m1;
void threadFunc()
{
	int count = 100000;
	//m1.lock();
	while(count--)
			++val;
	//m1.unlock();
}
int main()
{
	std::thread t1(threadFunc);
	std::thread t2(threadFunc);
	
	t1.join();
	t2.join();
	
	cout << "Value is: " << val << endl;
	return 0;
}

