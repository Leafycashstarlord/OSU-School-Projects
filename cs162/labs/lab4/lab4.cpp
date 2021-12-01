#include <iostream>
#include "lab4.h"

using namespace std;

//Default Constructor
Hand::Hand(){
	cout << "Inside Hand Default Constructor." << endl;
	this->hand_size = 10;
	this->hand_array[] = hand_array[hand_size];
	
	int counter = 0;
	for(int i = 0; i < hand_size; i++){
		hand_array[i] = counter;
		counter++:
	}
}

//Copy Constructor
Hand::Hand(const Hand& h){
	cout << "Inside Hand Copy Constructor." << endl;
	this->hand_size = h.hand_size;
	this->hand_array[] = h.hand_array[hand_size];
}

//Assignment Operator Overload
Hand& Hand::operator=(const Hand& h){
	cout << "Inside Assignment Operator Overload." << endl;
	if(this != &h){
		delete [] hand_array;
		
		this->hand_size = h.hand_size;
		this->hand_array[] = h.hand_array[hand_size];
	}
}

//Destructor
Hand::~Hand(){
	cout << "Inside Destructor." << endl;
	delete[] hand_array;
}
