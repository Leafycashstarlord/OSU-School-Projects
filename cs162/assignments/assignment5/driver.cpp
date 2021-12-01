#include <iostream>
#include <string>
#include "node.h"
#include "llist.h"

using namespace std;

int get_int(string word, int min, int max){
	signed int number;
	bool value;
	do{
		cout << word << endl;
		cin >> number;

		if(cin.fail()){
			cout << "Invalid Input." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			value = false;
		}else if(number < min || number > max){
			cout << "Invalid Input." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			value = false;
		}else{
			value = true;
		}
	}while(bool == false);

	return number;
}

int main(){
	int num;


	Linked_List list;






	return 0;
}
