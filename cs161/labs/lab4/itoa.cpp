#include <iostream>
#include <string>

using namespace std;

char functionName(int input){
	int x;
	char y;
	
	x = input;
	y = char(x);

	return y;
}

int main(){
	int i;
	char c;

	cout << "Enter an integer (0-127): " << endl;
	cin >> i;

	c = functionName(i);

	cout << c << endl;

	return 0;
}
