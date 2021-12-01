/*****************
 *Author: Jackson E. Rollins
 * **************/
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "pogwarts.h"

using namespace std;
/*****
 *Main function that runs the whole program. Takes in 2 parameters as command line arguments, of which they are text files the user gives.
 ********/
int main(int argc, char** argv){
	if(argc == 3){
		wizard user;
		fstream file;
		ifstream final_file;
		bool logged_in = login(argv, user, file);
		if(logged_in  == false){
			cout << "Invalid login." << endl;
			return 1;
		}
		int number_of_books = get_book_number(argv, file);
		spellbook* spellbooks = create_spellbooks(number_of_books);
		final_file.open(argv[2]);
		get_spellbook_data(spellbooks, number_of_books, final_file);
		cout << "hello" << endl;
		sort_books(spellbooks, user, number_of_books, file);
		delete_info(spellbooks, number_of_books);
	}else{
		cout << "Invalid file input." << endl;
	}
	
	cout << "Come again soon!" << endl;
	return 0;
}
