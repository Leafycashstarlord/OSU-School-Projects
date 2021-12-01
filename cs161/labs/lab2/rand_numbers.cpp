#include <iostream>
#include <ctime> /*included to allow time() to be used*/
#include <cstdlib> /*included to allow rand() and srand() to be used*/

using namespace std;

int main(){
	int num;
	int numb;
	srand(time(NULL));

	num = rand();
	numb = num % 6;

	if (numb == 0){
		cout << "Bummer, I'm zero!!!" << endl;
	}
	else if ((numb % 2) == 1){
		cout << "I'm an odd number!" << endl;
		if (numb == 1){
			cout << "I'm the number 1!" << endl;
		}
		else if (numb == 3){
			cout << "I'm the number 3!" << endl;
		}
		else if (numb == 5){
			cout << "I'm the number 5!" << endl;
		}
	}
	else if ((numb % 2) == 0){
		cout << "I'm an even number!" << endl;
		if (numb == 2){
			cout << "I'm the number 2!" << endl;
		}
		else if (numb == 4){
			cout << "I'm the number 4!" << endl;
		}
	}

	return 0;
}
