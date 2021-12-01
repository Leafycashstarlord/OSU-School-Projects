#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
	int passLen;
	int numbers;
	int letters;
	int numCount;
	int running = 0;
	int uppercase;
	int lowercase;
	int upperCount;
	int lowerCount;
	int x;
	char y;
	srand(time(NULL));

	string userPassword;

	cout << "How long do you want the password to be?: " << endl;
	cin >> passLen;
	cout << "Do you want any numbers? (0-no, 1-yes): " << endl;
	cin >> numbers;
	if (running < passLen){
		if (numbers == 1){
			cout << "How many numbers do you want?: " << endl;
			cin >> numCount;
			running = running + numCount;
			if (running > passLen){
				cout << "Exceeds the length of the password!";
			}
		}
	}
	if (running < passLen){
		cout << "Do you want any letters? (0-no, 1-yes): " << endl;
		cin >> letters;
	
		if (letters == 1){
			cout << "Do you want any uppercase letters? (0-no, 1-yes): " << endl;
			cin >> uppercase;
			if (uppercase == 1){
				cout << "How many uppercase letters do you want?: " << endl;
				cin >> upperCount;
				running = running + upperCount;
				if (running > passLen){
					cout << "Exceeds the length of the password!";
				}
			}
			if (running < passLen){
				cout << "Do you want any lowercase letter? (0-no, 1-yes): " << endl;
				cin >> lowercase;
				if (lowercase == 1){
					cout << "How many lowercase letter do you want?: " << endl;
					cin >> lowerCount;
					running = running + lowerCount;
					if (running > passLen){
						cout << "Exceeds the length of the password!";
					}
				}
			}
		}

		
	}

	if (running == passLen){
		if (numbers == 1){
			for(int i = 0; i < numCount; i++){
				x = rand();
				y = (x % 10) + 48;
				userPassword.append('y');
			}
		}
		else if(uppercase == 1){
			for(int i = 0; i < upperCount; i++){
				x = rand();
				y = (x % 26) + 97;
				userPassword.append('y');
			}
		}
		else if(lowercase == 1){
			for(int i = 0; i < lowerCount; i++){
				x = rand();
				y = (x % 26) + 65;
				userPassword.append('y');
			}
		}
	}
	cout << userPassword << endl;
	
	return 0;
}
