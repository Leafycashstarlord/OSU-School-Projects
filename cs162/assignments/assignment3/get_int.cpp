/**************
 *Program: get_int.cpp
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Implemntation file for the get_int function
 * ************/
#include <iostream>
#include <string>
#include "get_int.h"

using namespace std;

//Function that takes in a question of rthe user, and a range of values, and asks the user for inputs until they get within the range
int get_int(string word, int min, int max){
	int number;
	bool value;
	do{
		cout << word << endl;
		cin >> number;

		if(cin.fail()){
			cout << "Invalid input." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			value = false;
		}else if((number < min) || (number > max)){
			cout << "Invalid input." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			value = false;
		}else{
			value = true;
		}

	}while(value == false);

	return number;
}
