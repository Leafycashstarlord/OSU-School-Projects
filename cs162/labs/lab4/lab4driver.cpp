#include <iostream>
#include "lab4.h"

using namespace std;

int main(){
	Hand hand1;
	cout << "hand1: " << endl;
	hand1.print();
	
	Hand hand2 = hand1;
	cout << "hand2: " << endl;
	hand2.print();

	Hand hand3 = Hand(5);
	cout << "hand3: " << endl;
	hand3.print();

	hand1 = hand3;
	cout << "hand1: " << endl;
	hand1.print();

	cout << "hand2: " < endl;
	hand2.print();

	return 0;
}
