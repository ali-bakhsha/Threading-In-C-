//TOPIC: Type of thread creation in c++ 11
//There are 5 diffrent types we can create threads in c++11 using callable objects

//Notes
// If we create mutable threads at the same time it doesn't qurantee which one will start first.

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

/*
											//1. Function Pointer
//This is very basic form of thread creation

void func(int x)
{
	while(x-- > 0)
		cout << x << endl;
}
int main()
{
	auto startTime = std::chrono::high_resolution_clock::now();
	//1. Function Pointer ////////
	std::thread t1(func, 10);
	std::thread t2(func, 10);
	
	t1.join();
	t2.join();
	auto stopTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
	cout << "The duration is " << duration.count() / 1000000.0 << "s" << endl;
	//////////////////////////////
	return 0;
}*/

											//2. Lambda function
// Example
/*int main(){
	
	auto func = [](int x){
		while(x-- >0)
			cout << x << endl;
		
	};
	std::thread t1(func , 10);
	std::thread t2([](int x){ while(x-- > 0) cout << x << endl;} , 10);
	t1.join();
	t2.join();
	return 0;
}*/

											//3. Functor (Function Objects)
// Example
/*class Base{
	public:
		Base() = default;
		void operator()(int x){
			while(x-- > 0)
				cout << x << endl;
		}
};
int main()
{
	std::thread t1(Base() , 10);
	std::thread t2(Base() , 20);
	t1.join();
	t2.join();
	return 0;
}*/

											//4. non-static member function
// Example
/*class Base{
	public:
		void run(int x){
			while(x-- > 0)
				cout << x << endl;
		}
};
int main()
{
	Base b;
	std::thread t1(&Base::run ,&b ,  10);
	std::thread t2(&Base::run ,&b ,  10);
	t1.join();
	t2.join();
	return 0;
}*/

											//5. static member function
// Example
class Base{
	public:
		static void run(int x){
			while(x-- > 0)
				cout << x << endl;
		}
};
int main()
{
	std::thread t1(&Base::run ,  10);
	std::thread t2(&Base::run  ,  10);
	t1.join();
	t2.join();
	return 0;
}