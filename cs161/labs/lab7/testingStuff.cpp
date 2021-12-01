#include <iostream>

using namespace std;

void thing1(int *y){
	int *add = new int
	*add = 10;
	(*y) += (*plus);

	delete plus;
	plus = NULL;
}

void thing2(int *y){
	int *subtract = new int;
	*subtract = -5;
	(*y) += (*subtract);

	delete subtract;
	subtract = NULL;
}

void thing3(int *y){
	int *zero = new int;
	*zero = 0;
	(*y) = (*zero);

	delete zero;
	zero = NULL;
}

int main(){
	int *y = new int;

	cout << "Give an integer: " << endl;
	cin >> y;

	cout << thing1(y) << endl;
	cout << thing2(y) << endl;
	cout << thing3(y) << endl;

	delete y;

	return 0;
}
