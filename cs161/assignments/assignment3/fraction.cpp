/***************
 *Program: Fraction.cpp
 *Author: Jackson E. Rollins
 *Date: 2/16/2020
 *Description: Take sa fraction given by the user, and prints out the fraction in its simplest form
 *Input: A numerator and denominator, both integers
 *Output: One or two integers int eh form of a fraction or a single integer, whichever is the ismplest form of the users input
 ******************/

#include <iostream>

using namespace std;

/***************
 *Function: g_c_d()
 *Description: Finds the greatest common divisor between the numerator and denominator of a function
 *Parameters: int num1, int num2
 *Pre-Conditions: Take integer parameters
 *Post-Conditions: return an int value that represents the greatest common divisor
 * *************/
int g_c_d(int num1, int num2){
	if(num2 == 0){
		return num1;
	}else{
		return g_c_d(num2, (num1 % num2));
	}
}
/*******************
 *Function: to_lowest_terms
 *Description: Takes the users given function, and reduces it to its simplest form usign the divisor
 *Parameters: int &numerator, int &denominator
 *Pre-conditions: Takes in integer parameters
 *Post-Conditions: Returns true or false if the fraction was simplisfied or not
 * ******************/
bool to_lowest_terms(int &numerator, int &denominator){
   	int divisor;
   	divisor = g_c_d(numerator, denominator);
	numerator = numerator / divisor;
	denominator = denominator / divisor;

	if(denominator == 0){
		return false;
	}else{
		return true;
	}

}
/********************
 *Function: main()
 *Description: Runs the program, reason it is longer than 15 lines is due to all the error handling. 
 *Parameters: None
 *Pre-conditions:nothing
 *Post-conditions:Prints out the simplified number
 * *****************/
int main(){
	char runAgain;
	bool agane;
	int numerator;
	int denominator;
   	do{
		do{
   			cout << "Enter a numerator (Integers Only): " << endl;
       			cin >> numerator;
			if(cin.fail() == true){
				cout << "Invalid Input!" << endl;
				cin.clear(); 
				cin.ignore(10000, '\n'); 
			}else{
				break; 
			}	
		}while(true);
		do{ 
			cout << "Enter a denominator (Integers that aren't Zero Only): " << endl;
			cin >> denominator;
			if((cin.fail() == true) or denominator == 0){
				cout << "Invalid Input!" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}while((cin.fail() == true) or denominator == 0);

		to_lowest_terms(numerator, denominator);

		if(numerator % denominator == 0){
			cout << "The lowest terms of your fraction: " << (numerator / denominator) << endl;
		}else{
			cout << "The lowest terms of your fraction: " << numerator << "/" << denominator << endl;
		}
		do{
			cout << "Do you want to do another conversion? (y/n): " << endl;
			cin >> runAgain;
			if((runAgain != 'y') and (runAgain != 'n')){
				cout << "Invalid Input!" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}while((runAgain != 'y') and (runAgain != 'n'));

		if(runAgain == 'y'){
			agane = true;
		}else if(runAgain == 'n'){
			agane = false;
		}
	}while(agane == true);

	return 0;
}
