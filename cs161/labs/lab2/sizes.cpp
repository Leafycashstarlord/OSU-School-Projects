#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int number;
	int bitSize;

	cout << "Enter number of bits: ";
	cin >> number;

	bitSize = (pow(2, number))-1;
	cout << "Maximum unsigned value that can be stored is: " << bitSize << endl;

	bitSize = (pow(2, number-1))-1;
	cout << "Maximum signed value that can be stored is: " << bitSize << endl;

	bitSize = -1*(pow(2, number-1));
	cout << "Minimum signed value that can be stored is: " << bitSize << endl;

	return 0;
}
