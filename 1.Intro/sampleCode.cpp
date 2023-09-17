// TOPIC: Introduction to thread in C++ (C++ 11)

// Questions
//1. What do you undrestand by thread and give one example in c++?

//Answers
//1. In every Application there is a default thread which is main(), in side this we create other threads.
//2. A Thread is also known as lightweight process. Idea is achive parallelism by dividing a process into multiple threads. 
// 	For example:
//		(a) The browser has multiple tabs that can be diffrent threads.
//		(b) The Word must be using multiple threads, one thread to format the text, onother to process inputs(spell checker)
//		(c) Visual studio code editor would be using threading for auto completing the code. (Intelligence)	

// WAYS to create thread in C++ 11
// 1. Function Pointers
// 2. Lambda Functions
// 3. Functors
// 4. Member Functions
// 5. Static member Functions

// Requirements
// find the addition of all odd number from 1 to 1900000000 and all even number from 1 to 1900000000

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
ull oddSum 	= 0;
ull evenSum = 0;
void findEven(ull start , ull end){
	for (ull i = start; i < end; i++){
		if((i&1) == 0)
			evenSum+=i;
		//cout << "EVEN"<< endl;;
	}
}
void findOdd(ull start , ull end){
	for (ull i = start; i < end; i++){
		if((i&1) == 1)
			oddSum+=i;
		//cout << "ODD" << endl;
	}
}
int main()
{
	ull start = 1;
	ull end = 1900000000;
	
	auto startTime = std::chrono::high_resolution_clock::now();
	
	//findEven(start , end); // single thread mode
	//findOdd(start , end); // single thread mode

	// thread mode
	std::thread t1(findEven , start, end);
	std::thread t2(findOdd , start, end);
	
	t1.join();
	t2.join();
	
	
	auto stopTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime-startTime);

	cout << "Odds: \t\t" << oddSum << endl; 
	cout << "Evens: \t\t" << evenSum << endl << endl; 
	
	cout << "Duration: \t\t" << duration.count() / 1000000.0 << " s" << endl;
	return 0;
}