//TOPIC: std::mutex::try_lock() on mutext in C++11 threading


// 1. try_lock() tries to lock the mutext, returns immediatelly. on successfull lock acquisition return true otherwise return false.
// 2. if try_lock() is not able to lock mutex, then it doesn't get blocked. that is why it is called non-blocking.
// 3. if try_lock() is called again by the same thread which owns the mutex, the behavior is undefined.
//  It is dead lock situation with undefined behavior.( if you want to be able to lock the same mutex by same thread more than one time, then go for recursive_mutex)



// there are so many try_lock function
// 1. std::try_lock
// 2. std::mutex::try_lock
// 3. std::shared_lock::try_lock
// 4. std::timed_mutex::try_lock
// 5. std::unique_lock::try_lock
// 6. std::recursive_mutex::try_lock
// 7. std::shared_mutex::try_lock
// 8. std::shared_timed_mutex::try_lock
// 9. std::recursive_timed_mutex::try_lock

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;
std::mutex m;
void increaseTheCounterFor100000Times(){
	for(int i = 0; i < 100000; ++i) 
		if( m.try_lock()){
					//m.try_lock();

			counter++;
			m.unlock();
		}
}
int main()
{
	//1
/*	std::thread t1(increaseTheCounterFor100000Times);
	t1.join();
	cout << "Counter could increase upto: " << counter << endl;*/

	
	//2
	std::thread t1(increaseTheCounterFor100000Times);
	std::thread t2(increaseTheCounterFor100000Times);
		
	t1.join();
	t2.join();
	
	cout << "Counter could increase upto: " << counter << endl;
	
	return 0;
}
