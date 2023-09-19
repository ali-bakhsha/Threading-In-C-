//TOPIC: Condition Variables in c++ threading (std::condition_variable cv)

// IMPORTANT POINT : cv is used for two purpose:
// A. notify other threads
// B. waiting for some conditions

//Notes:
// 1. condition variables allow running threads to wait on some conditions and once those conditions are met the waiting thread is notified using:
//	a. notify_one()
//  b. notify_all()
// 2. You need mutext to use condition variables.
// 3. if some thread want to wait on some condition then it has to do this thing
//	a. acquire the mutex lock using std::unique_lock<std::mutex> lock(m)
//  b. execute wait, wait_for, wait_untill. the wait operations automatically release the mutex and suspend the execution of thread.  *****************
//  c. when the condition variable is notified , the thread is awaked and the mutex is automatically reacquired.
//     the thread should then check the condition and resume waiting if the wakeup was suprious


//Notes
// 1. condition variables are used to synchronize two or more threads
// 2. best the use of condition variable is producer/consumer problem.


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std;

std::mutex m1;
int balance = 0;
std::condition_variable cv;

void addMoney(int money)
{// producer
	//std::unique_lock<std::mutex> lock(m1);
	std::lock_guard<std::mutex> lg(m1);
	balance+= money;
	cout << "add money successfully : " << money << " And the balance is: " << balance << endl; 
	//cv.notify_one();
	cv.notify_all();
}
void withdrawMoney(int money)
{// consumer

	std::unique_lock<std::mutex> ul(m1);
	
	cv.wait( ul ,   []{return (balance!=0)?true:false;});
	
	if(balance >= money) 
		cout << "Amount Deducted : " << money << endl;
	else
		cout << "Amount can not be Deducted , current balance is less than " << money << endl;
	cout << "current balance is " << balance << endl;
	
}

int main()
{
	std::thread t1(addMoney , 500);
	std::thread t2(withdrawMoney , 600);
	std::thread t3(withdrawMoney , 600);
	
	t1.join();
	t2.join();
	t3.join();
	return 0;
}

