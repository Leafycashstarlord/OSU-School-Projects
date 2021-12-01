#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

void fun(int *a, int size){
	int zero = 0;
	int one = 0;

	for(int i = 0; i < size; i++){
		if(a[i] == 0){
			zero++;
		}
		if(a[i] == 1){
			one++;
		}
	}

	cout << "Number of 1s in the array: " << one << endl;
	cout << "Number of 0s in the array: " << zero << endl;
}

int main(){

	int size;
	int *user_array;
	int x;
	srand(time(NULL));

	cout << "How big do you want the array to be? (positive integer please); " << endl;
	cin >> size;

	user_array = new int[size];
	for(int i = 0; i < size; i++){
		x = rand() % 2;
		user_array[i] = x;
	}

	fun(user_array, size);
	delete [] user_array;

	return 0;
}
