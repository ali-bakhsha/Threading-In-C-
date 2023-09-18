//TOPIC: std::try_lock() in c++ 11 threading


// 1. std::try_lock() tries to lock all the lockable objects passed in it one by one in given order

	// SYNTAX: std::try_lock(m1,m2,m3,m4,...)
// 2. On success this function returns -1 otherwise it will return 0-based mutex index number which could not lock,
// 3. if it fails to lock any of the mutex then it will release all the mutex it locked before.
// 4. if a call to try_lock returns in an exception, unlock is called for any locked object before rethrowing.


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

int X = 0;
int Y =0;

std::mutex m1, m2;

void doSomeWorkForSeconds(int seconds) { std::this_thread::sleep_for(std::chrono::seconds(seconds));}

void incrementXY(int &XorY , std::mutex&m , const char* desc)
{
	for(int i =0; i < 10; i++){
		m.lock();
		++XorY;
		cout << desc << XorY << endl;
		m.unlock();
		doSomeWorkForSeconds(1);
	}
}

void consumeXY(){
	int useCount =10;
	int XplusY = 0;
	
	while(1)
	{
		int lockResult = std::try_lock(m1 , m2);
		if(lockResult != -1)
		//cout << "REEEEEE : " << lockResult << endl;
		if(lockResult == -1)
		{
			if (X != 0 && Y !=0){
				--useCount;
				XplusY += (X+Y);
				X = 0; 
				Y = 0;
				cout << "XplusY: " << XplusY << endl;
			}
			m1.unlock();
			m2.unlock();
			if(useCount == 0) break;
		}
	}
}


int main()
{
	std::thread t1(incrementXY , std::ref(X) , std::ref(m1) , "X ");
	std::thread t2(incrementXY , std::ref(Y) , std::ref(m2) , "Y ");
	std::thread t3(consumeXY);		
		
	t1.join();
	t2.join();
	t3.join();
	
	
	return 0;
}
