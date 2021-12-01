#include <iostream>
#include <string>

using namespace std;

int main(){
	char string[256];
 	int word; 

	cout << "Give a sentence/paragraph no longer than 256 characters: " << endl;
	cin.getline(string, 256);
	
	if(cin.fail()){
		cin.ignore(256, '\n');
		cin.clear();
	}
	
	cout << "How many words do you want to check? (positive integer): " << endl;
	cin >> word;

	string  words[] = {0};
	
	for(int i = 0; i < word; i++){
		cout << "Please give a word: " << endl;
		getline(cin, words[i]);
	}


	cout << string[256] << endl;
	for(int i = 0; i < word ; i++){
		cout << words[i] << ", ";
	}
	endl;

	return 0;
}
