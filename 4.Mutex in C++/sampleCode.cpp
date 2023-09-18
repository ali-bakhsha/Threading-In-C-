//TOPIC: Mutex in C++ threading | why use Mutex? what is race condition and how to silve it? what is the critical section

// Mutex Mutual exclusion
//Race condition:
// 1. Race condition is a situation where two or more threads/process happend to change a common data at the same time.
// 2. if there is a race condition then we have to protect it and the protected section is called critical section/region


//Mutex:
// 1. Mutex is used to avoid race condition
// 2. we use lock() , unlock() on mutext to avoid race condition.

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int myAmount = 0;
std::mutex m;
void addMony(){
	m.lock();
		myAmount++;
	m.unlock();
}
int main()
{
	std::thread t1(addMony);
	std::thread t2(addMony);
	
	
	t1.join();
	t2.join();
	
	cout << "My Amount: " << myAmount << endl;
	return 0;
}
