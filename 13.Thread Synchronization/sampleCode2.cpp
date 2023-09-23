//get a string , number of threads and count of charachter
//for example 
//abcdefg , 4 thread , charachter count 3
//T1 -> abc
//T2 -> def
//T3 -> gab
//T4 -> cde

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
using namespace std;

class MyPrinter{
		string strInput = ""; 
		int char_count = 0;
		int thread_count = 0;
	public:
		MyPrinter(string str , int chcount ,int  tcount): strInput(str) , char_count(chcount) , thread_count(tcount){}
		void run(){
			cout << "run" << endl;
		}
};
int main(int argc , char* argv[])
{
	if (argc !=4){
		cout << "please provide 3 arguments - a string , char count and thread count" << endl;
		return 1;
	}
	
	string str 			= argv[1];
	int char_count 		= atoi(argv[2]);
	int thread_count 	= atoi(argv[3]);
	
	MyPrinter p(str , char_count , thread_count);
	p.run();
	
	
	
	return 0;
}

