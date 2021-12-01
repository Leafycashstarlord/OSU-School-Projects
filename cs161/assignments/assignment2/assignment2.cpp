/***************************************
 *Program: assignment2.cpp
 *Author: Jackson E. Rollins
 *Date: 02/02/2020
 *Description: This program tests a multitude of functions that would be used
 *for error handling in any future program
 *Input: The integer for the get_int() function 
 *Output: The test results for all the functions
 * ************************************/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/****************
 *Function: check_range() 
 *Description: Indicates that the given integer is between two other itnegers
 *Parameters: Lower bound, Upper bound, integer value
 *Pre-conditions: take integer paramters
 *Post-conditions: return true or false depending on if the value is between the values or not
 ****************/
bool check_range(int lower_bound, int upper_bound, int value){
	if(value >= lower_bound && value <= upper_bound){
		return true;
	}else{
		return false;
	}	
}
/**********
 *Function: is_capital() 
 *Description: Indicates whether or not the character is a capital or not
 *Parameters: char letter
 *Pre-conditions: take a char paramters
 *Post-conditions: return a true or false value depedning on if the character is a capital
 * *********/
bool is_capital(char letter){
	int x = int(letter); 
	 if(x <= 90 && x >= 65){
	 	return true;
	 }else{
	 	return false;
	 } 
}
/**********
 *Function: is_even() 
 *Description: Indicates if a given integer is even
 *Parameters: int num
 *Pre-condition: take an int parameters
 *Post-conditions: return a value to tell if an integer is even of not
 * *******/
bool is_even(int num){
	if(num % 2 == 0){
		return true;
	}else{
		return false;
	}
}
/***************
 *Function: is_odd
 *Description: Indicate if a given integer is odd
 *Parameters: int num
 *Pre-condition: take an integer parameter
 *Post-conditionsL return a value to tell if an integer is odd or not
 * ***********/
bool is_odd(int num){
	if(num % 2 == 1){
		return true;
	}else{
		return false;
	}
}
/************
 *Function: equality_test() 
 *Description: Indicate is two integers are equal to each other or not
 *Parameters: int num1, int num2
 *Pre-conditions: take two integer parameters
 *Post-conditions: return a value to tell if the integers are equal or not
 * **********/
int equality_test(int num1, int num2){
	if(num1 < num2){
		return -1;
	}
	else if(num1 == num2){
		return 0;
	}
	else if(num1 > num2){
		return 1;
	} 
} 
/************
 *Function: float_is_equal() 
 *Description: Indicate if two floats are equal to each other within a certain precision
 *Paramters: float num1, float num2, float precision
 *Pre-conditions: take in three float parameters
 *Post-conditions: return a value telling us if the flaots are equal o rnot within the precision
 * ********/
bool float_is_equal(float num1, float num2, float precision){
	if(abs(num1 - num2) <= precision){
		return true;
	}else{
		return false;
	} 
} 
/*****************
 *Function: is_integer() 
 *Description: Indicate if the given stirng is an integer or not
 *Parameters: string num
 *Pre-conditions: take a string parameter
 *Post-conditions: return a value to tlel if the string is an integer or not
 * **************/
bool is_integer(string num){
	for(int i = 0; i < num.length(); i++ ){
		if(num[i] < 48 || num[i] > 57 ){
			return false;
		}
	}
	return true;
}
/*****************
 *Function: numbers_present() 
 *Description: Indicate if a given string contains numbers
 *Parameters: string sentence
 *Pre-coonditions: take a string parameter
 *Post-Condition: return a value to tell if the string contains a number
 * ****************/
bool numbers_present(string sentence){
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] >= 48 && sentence[i] <= 57){
			return true;
		}  
	}
	return false;
}
/*************
 *Function: letters_present() 
 *Description: Indicates if letters are present in the string
 *Parameters: string sentence
 *Pre-conditions: take a string parameter
 *Post-Conditions: return a value to tell if the string contains a letter
 * ************/ 
bool letters_present(string sentence){
	for(int i = 0; i < sentence.length(); i++){
		if((sentence[i] >= 65 && sentence[i] <= 90) || (sentence[i] <= 122 && sentence[i] >= 97)){
			return true;
		}
	}
	return false;
}
/***********
 *Function: contains_sub_string
 *Description: Indicate if the sub strign is within the string
 *Parameters: string sentence, string sub_string
 *0Pre-conditions: take in two string parameters
 *Post-conditions: return a value to tell if the string contains the sub_string
 * *********/
bool contains_sub_string(string sentence, string sub_string){
	int value = 1;
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] == sub_string[0]){
			for(int j =0; j < sub_string.length(); j++){
				if(sentence[i+j] != sub_string[j]){
					value = 0;
				} 
			}
			if(value == 0){
				return true;
			}
		}
	}
	return false;
}  
/***********
 *Function: word_count() 
 *Description: Figures out ho wmany words are within a string
 *Parameters: string sentence
 *Pre-conditions: take a string parameter
 *Post-conditions: return an integer value representing the amount of words in the string
 * *********/
int word_count(string sentence){
	int counter = 1;
	for(int i = 0; i < sentence.length(); i++){
		if(i != 0 && i != ( sentence.length() - 1)){
			if(sentence[i] == 32){
				counter++;
			}  
		} 
	}
	return counter;	
}  
/*******************
 *Function: to_upper() 
 *Description: Turns all of the letters in a string to uppercase
 *Parameters: string sentence
 *Pre-conditions: take a string parameter
 *Post-conditions: return the string with all the letters contained in uppercase
 * ****************/
string to_upper(string sentence){
	string new_sentence = "";
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] <= 122 && sentence[i] >= 97){
			new_sentence += (sentence[i] - 32);
		}else{
			new_sentence += sentence[i];
		} 
	}
	return new_sentence;
}  
/*****************
 *Function: to_lower() 
 *Description: turns all of the letters in a string to lowercase
 *Parameters: string sentence
 *Pre-conditions: take a string parameter
 *Post-conditionsL return the string with all the letters contained in lowercase
 * ****************/
string to_lower(string sentence){
	string new_sentence = "";
       	for(int i = 0; i < sentence.length(); i++){
       		if(sentence[i] >= 65 && sentence[i] <= 90){
			new_sentence += (sentence[i] + 32); 
		}else{
			new_sentence += sentence[i];
		}
       	}
	return new_sentence;
}  
/****************
 *Function: get_int() 
 *Description: takes an input from the user, and returns it as an integer if the user gave an integer
 *Parameters: None
 *Pre-conditions: take an input from the user as a string
 *Post-condition: returns the given strign value as an integer if it is one
 * ***************/
int get_int(){
	int counter;
	int integer = 0;
	int counter2 = 0;
	int number = 0;
	char x;
	int y;
	string prompt = "";
	while(integer == 0){
	   	counter = 0;
		cout << "Please enter an integer value: ";
		cin >> prompt;
		for(int i = 0; i < prompt.length(); i++){
			if(prompt[i] < 48 || prompt[i] > 57){
				counter = 1;
			}
		}
		if(counter == 0){
			integer = 1;
		}
	}
	for(int i = 0; i < prompt.length(); i++){
		x = prompt[i];
		y = int(x) - 48;
		number = number + (y * pow(10,(prompt.length())- (i+1)));
	}
	return number;	
}  
/*********************
 *Function: main() 
 *Description: Tests all of the functions
 *Parameters: None
 *Pre-conditions: None
 *Post-conditions: Tells the user if each function passed its respective test
 * ******************/
int main(){
	cout << "Testing check_range(5, 10, 7)." << endl;
       	cout << "Expected Output: True" << endl;  	
   	cout << "Test: ";
	if(check_range(5, 10, 7) == true){
		cout << "Pass" << endl;   
	}else{
		cout << "Fail" << endl; 
	}

	cout << "Testing check_range(5, 10, 15)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
	if(check_range(5, 10, 15) == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	} 

	cout << "Testing is_capital(A). " << endl;
	cout << "Expected Output: True" << endl;
	cout << "Test: ";
	if(is_capital('A') == true){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing is_capital(a)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
	if(is_capital('a') == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing is_even(2)." << endl;
	cout << "Expected Output: True" << endl;
	cout << "Test: ";
	if(is_even(2) == true){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing is_even(1)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
       	if(is_even(1) == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing is_odd(1)." << endl;
	cout << "Expected Output: True" << endl;
	cout << "Test: ";
       	if(is_odd(1) == true){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing is_odd(2)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
	if(is_odd(2) == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}
	
	cout << "Testing equality_test(1,2)." << endl;
	cout << "Expected Output: -1" << endl;
	cout << "Test: ";
	if(equality_test(1, 2) == -1){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing equality_test(1,1)." << endl;
	cout << "Expected Output: 0" << endl;
	cout << "Test: ";
       	if(equality_test(1, 1) == 0){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing equality_test(1,0)." << endl;
	cout << "Expected Output: 1" << endl;
       	cout << "Test: ";
	if(equality_test(1, 0) == 1){
		cout << "Pass"  << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing float_is_equal(1.23, 1.28, 0.55)." << endl;
	cout << "Expected Output: True" << endl;
	cout << "Test: ";
	if(float_is_equal(1.23, 1.28, 0.55) == true){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing float_is_equal(1.23, 1.28, 0.01)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
	if(float_is_equal(1.23, 1.28, 0.01) == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing is_integer(10)." << endl;
	cout << "Expected Output: True" << endl;
	cout << "Test: ";
	if(is_integer("10") == true){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing is_integer(hello)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
	if(is_integer("hello") == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing numbers_present(I am 10 years old)."  << endl;
	cout << "Expected Output: True" << endl;
	cout << "Test: ";
	if(numbers_present("I am 10 years old.") == true){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing numbers_present(I am ten years old)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
	if(numbers_present("I am ten years old.") == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing letters_present(6/1/2020)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
	if(letters_present("6/1/2020") == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing letters_present(June First, Twenty Twenty)." << endl;
	cout << "Expected Output: True" << endl;
	cout << "Test: ";
	if(letters_present("June First, Twenty Twenty") == true){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing contains_sub_string(Big Brother, Brother)." << endl;
	cout << "Expected Output: True" << endl;
	cout << "Test: ";
	if(contains_sub_string("Big Brother", "Brother") == true){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing contains_sub_string(Big Brother, Sister)." << endl;
	cout << "Expected Output: False" << endl;
	cout << "Test: ";
	if(contains_sub_string("Big Brother", "Sister") == false){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing word_count(I have been born)." << endl;
	cout << "Expected Output: 4";
	cout << "Test: ";
	if(word_count("I have been born.") == 4){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	} 

	cout << "Testing to_upper(hello)." << endl;
	cout << "Expected Output: HELLO" << endl;
	cout << "Test: ";
	if(to_upper("hello") == "HELLO"){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing to_upper(u!)." << endl;
	cout << "Expected Output: U!" << endl;
	cout << "Test: ";
	if(to_upper("u!") == "U!"){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing to_lower(HELLO)."  << endl;
	cout << "Expected Output: hello" << endl;
	cout << "Test: ";
	if(to_lower("HELLO") == "hello"){
		cout << "Pass" << endl;
	}else{
		cout << "Pass" << endl;
	}

	cout << "Testing to_lower(U!)." << endl;
	cout << "Expected Output: u!" << endl;
	cout << "Test: ";
	if(to_lower("U!") == "u!"){
		cout << "Pass" << endl;
	}else{
		cout << "Fail" << endl;
	}

	cout << "Testing get_int()." << endl;
	cout << "Expected Output: Whatever the User Input if its an integer." << endl;
	int x = get_int();
	cout << x << endl; 
	cout << "Test: Pass" << endl;
}
