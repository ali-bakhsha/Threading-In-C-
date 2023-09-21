//TOPIC std::lock() in C++ 11

// it is used to lock multiple mutex at tge same time

// important 
//	1. syntax: std::lock(m1,m2,m3,m4)
//	2. all arguments are locked via a sequence of call to lock(), try_lock() , unlock() on each argument.
//	3 . order of locking is not defined (it will try to lock provided mutex in any order and ensure that there is no dead lock.
// 	4. it is a blocking call.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

std::mutex m1 , m2 , m3 , m4;
// we have 4 example, example 4 has deadlock 
void thread_task1()
{
	while(1){
	
// to see deadlock uncomment	std::this_thread::sleep_for(std::chrono::seconds(1));
		//example1 ,2 std::lock(m1 , m2);
		
		//example3 std::lock(m1 , m2 , m3 , m4);
		
		//example4 
		std::lock(m1 , m2); // deadlock
		//example4 
		std::lock(m3 , m4); // deadlock
		
		
		cout << "Task1 ..." << endl;
		
		// example1 , 2  m1.unlock(); 
		// example1 , 2 m2.unlock();
		
		
		// example3,4  
		m1.unlock(); 
		// example3,4  
		m2.unlock();
		// example3,4 
		m3.unlock(); 
		// example3,4  
		m4.unlock();
		
		
	}
}
void thread_task2()
{
	while(1){
//// to see deadlock uncomment std::this_thread::sleep_for(std::chrono::seconds(1));
		//example1 std::lock(m1 , m2); // 

		//example2 std::lock(m2 , m1); // 

		//example3 std::lock(m3 , m4); // 
		//example3 std::lock(m1 , m2); // 
		
		//example4 
		std::lock(m3 , m4); // deadlock
		//example4 
		std::lock(m1 , m2); // deadlock
		
		cout << "Task2 ..." << endl;
		
		//example1 m1.unlock(); 
		//example1 m2.unlock(); 
		
	
		//example2 m2.unlock(); 
		//example2 m1.unlock(); 
	
	
		//example3,4 
		m3.unlock(); 
		//example3,4 
		m4.unlock();
		//example3,4 
		m1.unlock(); 
		//example3,4 
		m2.unlock(); 
	
	}
}
int main()
{
	std::thread t1(thread_task1);
	std::thread t2(thread_task2);
	
	t1.join();
	t2.join();
	
	return 0;
}

