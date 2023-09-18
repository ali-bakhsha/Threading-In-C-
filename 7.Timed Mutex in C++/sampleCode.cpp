//TOPIC: std::timed_mutex in C++ threading

// std::timed_mutex m;
// m.try_lock_for( std::chrono::seconds(1)) -> return true or false

// auto now = std::chrono::steady_clock::now();
// m.try_lock_until(now + std::chrono::seconds(1)

// Notes:
// 1. std::timed_mutex is blocked till timeout_time or the lock is acquired and return true if success otherwise return false
// 2. Member functions:
//		a. lock()
//		b. try_lock()
//		c. try_lock_for
//		d. try_lock_until
//		e. unlock()

//Example try_lock_for
// wait untill specific timeout duration has elapsed or the lock is acquired. whichever comes first.
// on successfull lock acquisition returs true otherwise returns false

// for try_lock_untill it waits for a special time

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
int myAmount = 0;
std::timed_mutex m;


void increment(int i)
{
	
	//1.
	auto now = std::chrono::steady_clock::now();
	if( m.try_lock_until( now + std::chrono::seconds(2))){
	//2. if(m.try_lock_for(std::chrono::seconds(1))){ 
		cout << "enter successfull by thread id: " << i << endl;
		myAmount++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		m.unlock();
	}
	else
		cout << "can not enter by thread id: " << i << endl; 
	
	
}


int main()
{
	std::thread t1(increment , 1 );
	std::thread t2(increment , 2 );
		
	t1.join();
	t2.join();
	cout << " MyAmount: " << myAmount <<endl;
	
	return 0;
}
