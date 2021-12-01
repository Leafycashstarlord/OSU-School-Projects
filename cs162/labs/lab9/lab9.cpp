#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void print(int *array, int size){
	for(int i = 0; i < size; i++){
		cout << array[i] << " ";
	}
	cout << endl;
	cout << endl;
}

void selectionsort(int *array, int size){
	int num1, num2;
	for(int i = 0; i < size - 1; i++){
		num1 = i;
		for(int j = i+1; j < size; j++){
			if(array[j] < array[num1]){
				num1 = j;
			}
		}
		if(num1 != i){
			num2 = array[i];
			array[i] = array[num1];
			array[num1] = num2;
		}
	}
}

int get_int(string word, int min, int max){
	int num;
	bool value;
	do{
		cout << word << endl;
		cin >> num;

		if(cin.fail() || num > max || num < min){
			cout << "Invalid input!" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			value = false;
		}else{
			value = true;
		}
	}while(value == false);

	return num;
}

void printprime(int *array, int size){
	int counter = 0;
	int primeN[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 63, 79, 83, 89, 97};
	cout << "All the Prime Numbers in the list: " << endl;
	for(int i = 0; i < size; i++){
		for(int k = 0; k < 25; k++){
			if(array[i] == primeN[k]){
				cout << array[i] << " ";
				counter++;
			}
		}
	}
	if(counter == 0){
		cout << "There are no prime numbers!";
	}

	cout << endl;
	cout << endl;	
}

int main(){
	srand(time(NULL));
	int size;
	int num;
	size = get_int("How big is the list? (between 0-25)", 0, 25);
	int *array = new int[size];
	int *copy = new int[size];
	for(int i = 0; i < size; i++){
		num = rand()%100 + 1;
		array[i] = num;
	}

	for(int k = 0; k < size; k++){
		copy[k] = array[k];
	}

	cout << "Unfiltered list:" << endl;
	print(array, size);

	selectionsort(copy, size);
	cout << "Filtered list: " << endl;
	print(copy, size);

	printprime(copy, size);

	delete [] array;
	delete [] copy;
	return 0;
}
