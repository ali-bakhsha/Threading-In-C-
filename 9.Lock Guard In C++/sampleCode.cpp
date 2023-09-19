//TOPIC: lock gaurd in C++ (std::lock_gaurd<mutex> l(m1))


//Notes:
// 1. It is very lightweight wrapper for owning mutext on scopped basis
// 2. It aquires mutex lock the moment you create the object of lock gaurd
// 3. It automatically removes the lock while goes out of scope.
// 4. You can not explicitly unlock the lock_gaurd
// 5. You can not copy the lock_gaurd

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex m1;
int buffer = 0;

/*void task(const char* threadNumebr , int loopFor)
{
	m1.lock();
	for(int i =0; i < loopFor; ++i){
		buffer++;
		cout << threadNumebr << buffer << endl;
	}
	m1.unlock();
		
}

int main()
{
	std::thread t1(task , "T0 " , 10);
	std::thread t2(task , "T1 " , 10);
	
	t1.join();
	t2.join();
	return 0;
}*/

void task(const char* threadNumebr , int loopFor)
{
	//m1.lock();
	std::lock_guard<std::mutex> lock(m1);
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

