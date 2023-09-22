//TOPIC std::async in C++ threading

// syntax 
//	std::future = std::async(lunchmode , function , args)

// Notes
// 1. It runs a function asynchronously( potentialy in a new thread) and returns a std::future that will hold the result
// 2. There are three launch policies for creating task
//		a. std::launch::async   						-> create a thread with a diffrent thread id 
//		b. std::launch::deferred 						-> it will not create a separated thread and it is same block task
//		c. std::launch::async | std::launch::defered	-> os can select each of them

//how it works
// 1. It automatically creates a thread (or picks from internal thread pool) and promise object for us.
// 2. Then passes the std::promise object to thread function and returns the assotiated std::future object.
// 3. When ours passed argument function exsist then it's value will be set in this promise object. so eventualy return value will be available in std::future and can be get with std::future.get() function.

// Side Notes
// We can send Functor and lambda function as callback to std::async. It will work the same.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
using namespace std;
typedef unsigned long long ull;
ull oddFunc(  ull start , ull end)
{
	cout << "Function  thred ID: " << std::this_thread::get_id() << endl;

	ull sumofOdd = 0;
	for(ull i = start; i < end; i++){
		if(i&1)
			sumofOdd+=i;
	}
	return sumofOdd; 
}
int main()
{
	ull start = 0;
	ull end = 1900000000;
	
	
	
	cout << "main thred ID: " << std::this_thread::get_id() << endl;

	cout << "Ready to start async task ..." << endl;
	//std::future<ull> oddFuture = std::async(std::launch::deferred , oddFunc , start , end);
	//std::future<ull> oddFuture = std::async(std::launch::async , oddFunc , start , end);
	std::future<ull> oddFuture = std::async(std::launch::deferred | std::launch::async , oddFunc , start , end);
	
	cout << "OddSume is: " << oddFuture.get() << endl; 
	
	
	return 0;
}

