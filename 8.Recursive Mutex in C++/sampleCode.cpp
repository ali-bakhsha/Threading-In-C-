//TOPIC: std::recursive_mutex in C++ threading

//Notes:
// 1. It is same mutext but, same thread can lock one mutex multiple times using recursive_mutex
// 2. If thread T1 first call lock/try_lock on recursive mutex m1, then m1 is locked by T1, now as T1 is running in recursion T1 can call lock/try_lock any number of times there is no issue.
// 3. But if Ti have aquired 10 times lock/try_lock on mutex m1 then thread T1 will have to unlock it 10 times otherwise no other thread will be able to lock mutex.
//    it means recursive_mutex keeps count how many times it was locked so that many times it should be unlock.
// 4. How many time we can lock recursive_mutex is not defined but when that number reachesand if we were calling lock() it will return std::system_error or if we were calling try_lock() then it will return false. 

// BOTTON LINE
// 1. it is similar to mutex but have extra facility that it can be locked multiple time by same thread.
// 2. if we can avoid recursive_mutex then we should becuase it brings overhead to the system.
// 3. It can be used in loops also.

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

//Example 1 : with recursion
/*
int buffer = 0;
std::recursive_mutex m1;

void recursion(char c , int loopFor)
{
	if(loopFor < 0)
		return;
	
	m1.lock();
	cout << c << " " << buffer++ << endl;
	recursion(c , --loopFor);
	m1.unlock();
	cout << "Unlocked by thread " << c << endl;
}


int main()
{
	std::thread t1(recursion ,'a' ,10 );
	std::thread t2(recursion , 'b' , 10 );
		
	t1.join();
	t2.join();
	cout << " Buffer: " << buffer <<endl;
	
	return 0;
}*/

//Example 2 : with loop

std::recursive_mutex m1;

int main()
{
	for(int i=0; i < 5; ++i){
		m1.lock();
		std::cout << "Locked" << endl;
	}
	
	
	for(int i=0; i < 5; ++i){
		m1.unlock();
		std::cout << "unLocked" << endl;
	}
	return 0;
}

