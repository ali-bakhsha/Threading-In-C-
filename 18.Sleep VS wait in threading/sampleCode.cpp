//TOPIC sleep vs threading

//				Sleep															wait
//  SLEEP IS:															WAIT IS:
//  "I am done with my timeslice, and please don't						"I am done with my timeslice, Dont give me a another timeslice until someone calls notify_one() or notify_all()"
//  give me another one for at least m miliseconds"						As with slee(), The OS won't even try to schedule your task unless someone calls notify() or notify_all() 
//  The OS doesn't even try to schedule the sleeping 					(or a few other wakeup scenarios occurs)
//  thread until requested time has passed.


// POINTS:																POINTs:
// 1. It will keep the lock and sleep.									1.It releases the lock and wait.
// 2. Sleep is directly to thread, it is a thread function				2.Wait is on condition_variable, it is like there is a condition_variable in a thread and wait is applied to
//																		  that CV but it ends up putting thread in waiting state. 						

//
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <deque>
#include <condition_variable>
using namespace std;

std::mutex m;
std::condition_variable cv;
const unsigned int maxBufferSize = 50;
std::deque<int> buffer;
void producer( int val)
{
	while(val){
		std::unique_lock<mutex> locker(m);
		cv.wait(locker , [](){return buffer.size() < maxBufferSize;});
	
		buffer.push_back(val);
		
		cout << "Produced: " << val << endl;
		val--;
		
		locker.unlock();
		cv.notify_one();
	}
}
void consumer()
{
	while(true)
	{
		std::unique_lock<mutex> locker(m);
		cv.wait(locker , [](){return buffer.size() > 0;});
		
		int val = buffer.back();
		buffer.pop_back();
		
		cout << "Consumed: " << val << endl;
		locker.unlock();
		cv.notify_one();
		
		
		this_thread::sleep_for(std::chrono::milliseconds(30));
	}
}
int main()
{
		thread t1(producer , 100);
		thread t2(consumer);
		
		t1.join();
		t2.join();
	
	return 0;
}



/* sample result
Produced: 100
Produced: 99
Produced: 98
Produced: 97
Produced: 96
Produced: 95
Produced: 94
Produced: 93
Produced: 92
Produced: 91
Produced: 90
Produced: 89
Produced: 88
Produced: 87
Produced: 86
Produced: 85
Produced: 84
Produced: 83
Produced: 82
Produced: 81
Produced: 80
Produced: 79
Produced: 78
Produced: 77
Produced: 76
Produced: 75
Produced: 74
Produced: 73
Produced: 72
Produced: 71
Produced: 70
Produced: 69
Produced: 68
Produced: 67
Produced: 66
Produced: 65
Produced: 64
Produced: 63
Produced: 62
Produced: 61
Produced: 60
Produced: 59
Produced: 58
Produced: 57
Produced: 56
Produced: 55
Produced: 54
Produced: 53
Produced: 52
Produced: 51
Consumed: 51
Consumed: 52
Consumed: 53
Consumed: 54
Consumed: 55
Consumed: 56
Consumed: 57
Consumed: 58
Consumed: 59
Consumed: 60
Consumed: 61
Consumed: 62
Consumed: 63
Consumed: 64
Consumed: 65
Consumed: 66
Consumed: 67
Consumed: 68
Consumed: 69
Consumed: 70
Consumed: 71
Consumed: 72
Consumed: 73
Consumed: 74
Consumed: 75
Consumed: 76
Consumed: 77
Consumed: 78
Consumed: 79
Consumed: 80
Consumed: 81
Consumed: 82
Consumed: 83
Consumed: 84
Consumed: 85
Consumed: 86
Consumed: 87
Consumed: 88
Consumed: 89
Consumed: 90
Consumed: 91
Consumed: 92
Consumed: 93
Consumed: 94
Consumed: 95
Consumed: 96
Consumed: 97
Consumed: 98
Consumed: 99
Consumed: 100
Produced: 50
Produced: 49
Produced: 48
Produced: 47
Produced: 46
Produced: 45
Produced: 44
Produced: 43
Produced: 42
Produced: 41
Produced: 40
Produced: 39
Produced: 38
Produced: 37
Produced: 36
Produced: 35
Produced: 34
Produced: 33
Produced: 32
Produced: 31
Produced: 30
Produced: 29
Produced: 28
Produced: 27
Produced: 26
Produced: 25
Produced: 24
Produced: 23
Produced: 22
Produced: 21
Produced: 20
Produced: 19
Produced: 18
Produced: 17
Produced: 16
Produced: 15
Produced: 14
Produced: 13
Produced: 12
Produced: 11
Produced: 10
Produced: 9
Produced: 8
Produced: 7
Produced: 6
Produced: 5
Produced: 4
Produced: 3
Produced: 2
Produced: 1
Consumed: 1
Consumed: 2
Consumed: 3
Consumed: 4
Consumed: 5
Consumed: 6
Consumed: 7
Consumed: 8
Consumed: 9
Consumed: 10
Consumed: 11
Consumed: 12
Consumed: 13
Consumed: 14
Consumed: 15
Consumed: 16
Consumed: 17
Consumed: 18
Consumed: 19
Consumed: 20
Consumed: 21
Consumed: 22
Consumed: 23
Consumed: 24
Consumed: 25
Consumed: 26
Consumed: 27
Consumed: 28
Consumed: 29
Consumed: 30
Consumed: 31
Consumed: 32
Consumed: 33
Consumed: 34
Consumed: 35
Consumed: 36
Consumed: 37
Consumed: 38
Consumed: 39
Consumed: 40
Consumed: 41
Consumed: 42
Consumed: 43
Consumed: 44
Consumed: 45
Consumed: 46
Consumed: 47
Consumed: 48
Consumed: 49
Consumed: 50
*/
