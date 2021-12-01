#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void get_string(string *sentence){
	cout << "What is the given sentence?: " << endl;
	getline(cin, *sentence);
}

void set_replace_string(string sentence, string *copy){
	*copy = sentence;
	for(int i = 0; i < (*copy).length(); i++){
		if((*copy)[i] == ' '){
			(*copy)[i] = '-';
		}
	}
	cout << *copy << endl;
}

int get_search_replace(char letter, string sentence, string &copy){
	int counter = 0;
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] == letter){
			counter++;
		}
		if(sentence[i] == ' '){
			copy[i] = letter;
		}
	}

	cout << "Number of chosen letter: " <<  counter << endl;
	cout << copy << endl;
	return counter;
}

int main(){
	char letter;

	string *sentence = new string;
	get_string(sentence);

	string *copy = new string;
	set_replace_string(*sentence, copy);

	cout << "What letter do you want?: " << endl;
	cin >> letter;
	get_search_replace(letter, *sentence, *copy);

	return 0;
}
