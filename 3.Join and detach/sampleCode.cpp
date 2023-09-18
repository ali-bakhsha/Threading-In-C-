//TOPIC: use of join() detach() and joinable() in Thread in C++ (c++11)

//Join notes:
// 1. once a thread is started we wait for this thread to finish by calling join() function on thread object.
// 2. double join will result to program termination ( terminat called after throwing an instance of std::system_error invalid argument) runtime error
// 3. if needed, we should check thread is joinable before joining (using joinable function)

//Detach Notes:
// 1. this is used to detach newly created thread from the parent thread
// 2. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and double detach() will result into program termination]
// 3. if we have detached thread and main function is returning then the detached thread execution is suspended.

//Notes:
// Either join() or detach() should be called on thread object, otherwise during theread object's destructor it will terminate the program. because inside destructor it checks if thread is still joinable? if yes thenb it terminate the program.
// the moment that you create a thread, that thread will be marked as joinable and then later once you apply join() or detach() on that thread then it automatically becomes non-joinable.
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void run(int count){
	while(count-->0)
		cout << "Thread "<< count << " Run" << endl;
	std::this_thread::sleep_for(chrono::seconds(10));
	cout << "Thread Exit" << endl;
}
int main()
{
/*	
	//JOIN
	std::thread t1(run , 10);
	cout << "main " << endl;
	if( t1.joinable())
		t1.join();
	cout << "exit" << endl;*/
	
	//DETACH
	std::thread t1(run , 10);
	
	cout << "main " << endl;
	if( t1.joinable())
		t1.detach();
	//t1.detach();
	std::this_thread::sleep_for(chrono::seconds(1));
	//t1.join();
	cout << "exit" << endl;
	
	
	return 0;
}
