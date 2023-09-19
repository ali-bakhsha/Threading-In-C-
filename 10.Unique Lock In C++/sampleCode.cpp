//TOPIC: unique lock in c++ (std::unique_lock<mutex> lock(m1))


//Notes:
// 1. the class unique_lock is a mutex ownership wrapper
// 2. It allows:
// 	a. can have diffrent locking strategies
//  b. time constrained attemps at locking (try_lock_for , try_lock_until)
// 	c. recursive locking
//  d. transfer of lock ownership (move and copy)
//  e.condition variables (see this in comming ..)

// locking strategies
//		TYPE				EFFECTS
//	deffer_lock			do not acquire ownership of the mutex
//  try_to_lock			try to acquire ownership of the mutex without blocking
//  adopt_lock			assume the calling thread already has ownership of the mutex



#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

std::mutex m1;
int buffer = 0;

void task(const char* threadNumebr , int loopFor)
{
	//m1.lock();
	// 1. default strategy
		std::unique_lock<std::mutex> lock(m1); // automatically calls lock on mutex m1
	
	// 2. defer start 
		//std::unique_lock<std::mutex> lock(m1 , defer_lock); // does not call lock on mutex m1, beacuse use defer_lock. and you should explicitle call m1.lock, may be after some codes
		
		
		
		
					// some codes
		
		
		
		// lock.lock();
	// 2. defer end 
	
	// 
		//std::unique_lock<std::mutex> lock(m1 , try_to_lock); 
		//std::unique_lock<std::mutex> lock(m1 , adopt_lock); 
	//m1.lock();
	for(int i =0; i < loopFor; ++i){
		buffer++;
		cout << threadNumebr << buffer << endl;
	}
	//m1.unlock();
		
}

int main()
{
	std::thread t1(task , "T0 " , 10);
	std::thread t2(task , "T1 " , 10);
	
	t1.join();
	t2.join();
	return 0;
}

