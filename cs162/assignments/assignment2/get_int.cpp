/***********
 * Implementation file for get_int function
 * Author: Jackson E. Rollins
 * ***********/

#include <iostream>
#include <string>
#include "get_int.h"

using namespace std;

//Function that takes in a question for the user and returns the user's integer input
int get_int(string word){
	int number;
	bool value;
	do{
		cout << word << endl;
		cin >> number;

		if(cin.fail()){
			cout << "Invalid Input" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			value = false;
		}else{
			value = true;
		}
	}while(value == false);

	return number;
}
