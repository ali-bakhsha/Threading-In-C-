//Topic thread or process synchronization

// Note: we will use only thread example ro explain this topic

// Points
// 1. Thread or process synchronize to access critical section.
// 2. critical section in one or collection of program statement which should be executed by only one thread or process


#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
std::mutex m;
int bankBalance = 0;
void addMoney(int val)
{
	if(val <0 ) // here is not critical section
		return;
		
	m.lock();// you have synchronized
		// here is critical section
			bankBalance += val;
	// first 1- load bankBalance then 2- add to values and then 3-store
	// 2 threads can load the same value and here is critical section
	m.unlock(); 
	//here is not critical section because we dont change anything
	cout << bankBalance << endl;
}
int main()
{
	
	std::thread t1(addMoney, 100);
	std::thread t2(addMoney , 200);
	
	t1.join();
	t2.join();
	
	return 0;
}

