//TOPIC std::promise and std::future in C++ threading

// syntax 
//	std::promise<T> p , std::future<T> f

// They are very very interesting
// Notes
// std::promise
//			a. use to set values of exception.
// std::future
//			a. used to get values from promise
//			b. ask promise if the value is available 
//			c. wait for the promise


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
using namespace std;
typedef unsigned long long ull;
void thread_Func( std::promise<ull>&& prom , ull start , ull end)
{
	ull sumofOdd = 0;
	for(ull i = start; i < end; i++){
		if(i&1)
			sumofOdd+=i;
	}
	prom.set_value(sumofOdd); // when it is done go at .get at line 45
}
int main()
{
	ull start = 0;
	ull end = 1900000000;
	
	std::promise<ull> oddProm;
	std::future<ull> oddFuture = oddProm.get_future();
	
	cout << "Ready to start thread..." << endl;
	
	std::thread t1(thread_Func , std::move(oddProm) , start , end);
	cout << "Thread Created.. wait to complete promise by future get ..." << endl;
	
	cout << "OddSume is: " << oddFuture.get() << endl; // here is wait for set_value in line 30
	
	t1.join();
	
	return 0;
}

