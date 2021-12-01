#include <iostream>
#include <string>

using namespace std;

int functionName(char input){
	char x;
	int y;
	
	x = input;
	y = int(x);

	return y;
}
int main(){
	char c;
	int i;
	cout << "Enter a character: ";
	cin >> c;
	
	i = functionName(c);

	cout << i << endl;
	return 0;
}
