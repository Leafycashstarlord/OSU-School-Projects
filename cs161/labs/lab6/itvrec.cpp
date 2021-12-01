#include <iostream>
#include <sys/time.h>
#include <cstdlib>

using namespace std;

int fib_iter(int n){
	int tOne = 0;
	int tTwo = 1;
	int temp;
	
	if(n == 0){
		return 0;
	}else if(n == 1){
		return 1;
	}else{
   		for(int i = 1; i < n; i++){
			temp = tOne + tTwo;
			tOne = tTwo;
			tTwo = temp;
		}
		return temp;
	}
}

int fib_recurs(int n){
	if(n == 0){
		return 0;
	}else if(n == 1){
		return 1;
	}else{
		return (fib_recurs(n-1) + fib_recurs(n-2));
	}
}

int main(){
	typedef struct timeval time;
	time stop, start;
	
	int n;
	cout << "Which number of the Fibonacci Sequence do you want?: " << endl;
	cin >> n;

	gettimeofday(&start, NULL);

	//Time your interative or recursive function here.
	
	cout << fib_iter(n) << endl;

	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec){
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	}else{
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;
	}

	return 0; 
}
