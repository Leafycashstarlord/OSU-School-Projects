/***************
 *Jackson E. Rollins
 *6/7/2020
 *Driver file
 * ************/
#include <iostream>
#include <string>
#include "node.h"
#include "llist.h"

using namespace std;

//Get int function, asks the user for, and returns and integer
int get_int(string word, int num, int min, int max){
	signed int number;
	bool value;
	do{
		cout << word << endl;
		cin >> number;

		if(cin.fail()){
			cout << "Invalid Input." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			value = false;
		}else if(num == 1){
			if(number < min || number > max){
				cout << "Invalid Input." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				value = false;
			}
		}else{
			value = true;
		}
	}while(value  == false);

	return number;
}

//Function that checks to se if the given number is prim eor not, and returns true or false depending
bool isPrime(int num){
	bool value;
	for(int i = 0; i <= num/2; i++){
		if(num%1 == 0){
			value = true;
			break;
		}
	}
	if(value == true){
		return true;
	}else{
		return false;
	}
}

//Main function that runs the whole program. It is a little long because I made sure to showcase all of the givne functions.
int main(){
	int num;
	int num2;
	unsigned int num3;
	int num4;
	int num5;
	int num6;
	int counter;
	bool value;
	bool value2;

	do{
		num = get_int("Please enter a number: ", 0, 0, 0);
		Linked_List list = Linked_List(num);
		if(isPrime(num) == true){
			counter++;
		}
		while(value2 == false){
			num6 = get_int("Another Number? 1 for yes, 2 for no.", 1, 1, 2);
			if(num6 == 1){
				num = get_int("Enter a number: ", 0, 0, 0);
				num4 = get_int("Do want to push_front, push_back, or insert? 1 for front, 2 for back, 3 for insert.", 1, 1, 3);
				if(num4 == 1){
					num3 = list.push_front(num);
				}else if(num4 == 2){
					num3 = list.push_back(num);
				}else if(num4 == 3){
					num4 = get_int("Where in the list do you want to insert?: ", 1, 1, num3);
					num3 = list.insert(num, num4);
				}
				value2 = false;
				if(isPrime(num) == true){
					counter++;
				}
			}else if(num6 == 2){
				value2 = true;
			}
		}

		num5 = get_int("Do you want to sort ascending or descending? 1 for ascend, 2 for descend.", 1, 1, 2);
		if(num5 == 1){
			list.sort_ascending();
		}else if(num5 == 2){
			list.sort_descending();
		}

		cout << "Length of list is: " << list.get_length() << endl;
		cout << "You linked list is: ";
		list.print();
		cout << endl;
		cout << "Number of prime numbers in list: " << counter << endl;

		num2 = get_int("Do you want to go again? 1 for yes, 2 for no.", 1, 1, 2);
		if(num2 == 1){
			list.clear();
			value = false;
		}else if(num2 == 2){
			value = true;
		}
	}while(value == false);

	return 0;
}
