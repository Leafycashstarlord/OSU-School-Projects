/**********************
 *Program: pogwarts.cpp
 *Authoer: Jackson E. Rollins
 *Date: 4/12/2020
 *Description: A wizard school spellbook catalog
 *Input: Two text files
 *Output: User created files or requested data printed to screen
 * ***********************/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "pogwarts.h"

using namespace std;

//Function that deletes dynamic array info. Takes in a spellbook type and an integer. Doesn't return anything.
void delete_info(spellbook* spellbook_db, int spellbook_db_length){
	/*for(int i = 0; i < spellbook_db_length; i++){
		delete [] (*spellbook_db)[i];
	}*/
	delete [] spellbook_db;
}

//Function used to retrieve an integer from the user. Takes in a string parameter and returns an integer
int get_int(string word){
	int number;
	bool value;
	do{
	cout << word << endl;
	cin >> number;
	
	if(cin.fail()){
		cout << "Invalid input.";
		cin.clear();
		cin.ignore(10000, '\n');
		value = false;
	}else{
		value = true;
	}

	}while(value == false);

	return number;
}

//Function used to create the wizard login info database. Takes in a textfile, a file, and a database array. Returns an integer
int get_wizard_db(char** argv, wizard* &wizard_db, fstream &file){
	file.open(argv[1], ios::in);

	int number_of_wizards;
	file >> number_of_wizards;
	
	wizard_db = new wizard[number_of_wizards];

	for(int i = 0; i < number_of_wizards; i++){
		file >> wizard_db[i].name;
		file >> wizard_db[i].id;
		file >> wizard_db[i].password;
		file >> wizard_db[i].position_title;
		file >> wizard_db[i].beard_length;
	}

	file.close();
	return number_of_wizards;
}
//Function searches the database of wizard info to see if login was successfull or not. Takes in the database, two integers, a string, and a wizard type variable. Returns a boolean value
bool search_wizard_db(wizard* wizard_db, int number_of_wizards, int user_id, string user_password, wizard &user){
	for(int i = 0; i < number_of_wizards; i++){
		if(wizard_db[i].id == user_id && wizard_db[i].password == user_password){
			user = wizard_db[i];
			cout << "Welcome" << user.name << endl;
			cout << "ID: " << user.id << endl;
			cout << "Position: " << user.position_title << endl;
			cout << "Beard Length: " << user.beard_length << endl;
			return true;
		}
	}
	
	return false;
}

//Function that tries to log the user into the catalog system. Takes in a char varible, wizard type variable, and a file. Returns a boolean value.
bool login(char** argv, wizard &user, fstream &file){
	wizard* wizard_db;
	bool match;
	int user_id;
	string user_password;
	int number_of_wizards = get_wizard_db(argv, wizard_db, file);
	
	for(int i = 0; i < 3; i++){
		user_id = get_int("ID: ");
		cout << "Input Password: " << endl;
		cin >> user_password;
		match = search_wizard_db(wizard_db, number_of_wizards, user_id, user_password, user);
		if(match == true){
			delete [] wizard_db;
			return true;
		}	
	}
	cout << "hello" << endl;
	delete [] wizard_db;
	return false;
}

//Function that finds the amount of spellbook sin the catalog. Takes in a char variable, and a file. Returns an integer
int get_book_number(char** argv, fstream &file){
	int number_of_books;
	file.open(argv[2], ios::in);
	file >> number_of_books;
	file.close();
	return number_of_books;
}

//Function that creates a spellbook type array. Takes in an integer and returns a spellbook type variable
spellbook* create_spellbooks(int number_of_books){
	spellbook* spellbooks = new spellbook[number_of_books];
	return spellbooks;
}

//Function that retrieves the spellbook data from a file and puts in it a spellbook type array. Takes in a spellbook type variable, integer, and a file. Doesn't return anything
void get_spellbook_data(spellbook* spellbooks, int number_of_spellbooks, ifstream &final_file){
	float total;
	cout << "hello" << endl;
	for(int i = 0; i < number_of_spellbooks; i++){
		final_file >> spellbooks[i].title;
		final_file >> spellbooks[i].author;
		final_file >> spellbooks[i].num_pages;
		final_file >> spellbooks[i].edition;
		final_file >> spellbooks[i].num_spells;
		spellbooks[i].s = create_spells(spellbooks[i].num_spells);
		get_spell_data(spellbooks[i].s, spellbooks[i].num_spells, final_file);
		for(int j = 0; j < spellbooks[i].num_spells; j++){
			total += spellbooks[i].s[j].success_rate;
		}
		spellbooks[i].avg_success_rate = total/(spellbooks[i].num_spells);
		total = 0;
	}
	final_file.close();
}

//Function that creates a spell type array. Takes in an integer and returns a spell type variable
spell* create_spells(int number_of_spells){
	spell* spell_list = new spell[number_of_spells];
	return spell_list;
}

//Function the retrieves the spell data from a text file and puts it into a spell type array. Takes in a spell type variable, integer, and a file. Doesn't return anything
void get_spell_data(spell* spell_list, int number_of_spells, ifstream &final_file){
	for(int i = 0; i < number_of_spells; i++){
		final_file >> spell_list[i].name;
		final_file >> spell_list[i].success_rate;
		final_file >> spell_list[i].effect;
	}
}

//Function that does all the sorting. Takes in a spellbook type variable, wizard type, integer, and a file.
void sort_books(spellbook* spellbooks, wizard user, int number_of_books, fstream &file){
	int choice;
	bool stop;
	do{
		cout << "Sort spellbooks by number of pages, press 1." << endl;
		cout << "Sort spells by effect, press 2." << endl;
		cout << "Sort spellbooks by average success rate of contained spells, press 3." << endl;
		cout << "Close program, press 4." << endl;
		choice = get_int("What is your choice?: ");
		
		if(choice == 1){
			sort_by_page_num(spellbooks, user, number_of_books, file);
			stop = false;
		}else if(choice == 2){
			sort_by_spell_effect(spellbooks, user, number_of_books, file);
			stop = false;
		}else if(choice == 3){
			sort_by_avg_success(spellbooks, user, number_of_books, file);
			stop = false;
		}else if(choice == 4){
			stop = true;
		}else{
			cout << "Invalid Option." << endl;
			stop = false;
		}
	}while(stop == false);
}

//Function that prints out data to a file. Takes in a spellbook type, 2 integers, wizard type, string, and a file. Doesn't return anything
void file_print(spellbook* spellbooks, int num, int number_of_books, wizard user,  string sort_type, fstream &file){
	string new_file;
	cout << "What is the file you want to write to?: " << endl;
	cin >> new_file;
	file.open(new_file.c_str(), ios::out | ios::app);
	
	bool value;
	file << sort_type << endl;
	for(int i = 0; i < number_of_books; i++){
		if(user.position_title == "Student"){
			for(int j = 0; j < spellbooks[i].num_spells; j++){
				if(spellbooks[i].s[j].effect == "poison" || spellbooks[i].s[j].effect == "death"){
					value = false;
				}
			}
		}
		if(num == 1){
			if(value == true){
				file << spellbooks[i].title << " " << spellbooks[i].num_pages << endl;
			}
		}else if(num == 2){
			if(value == true){
				file << spellbooks[i].title << " " << spellbooks[i].avg_success_rate << endl;
			}
		}
		value = true;
	}
	file.close();
}

//Function that prints data out to screen. Takes in a spellbook type, 2 integers, wizard type, and a string. Doesn't return anything
void screen_print(spellbook* spellbooks, int num, int number_of_books, wizard user, string sort_type){
	bool value;
	cout << sort_type << endl;
	for(int i = 0; i < number_of_books; i++){
		if(user.position_title == "Student"){
			for(int j = 0; j < spellbooks[i].num_spells; j++){
				if(spellbooks[i].s[j].effect == "poison" || spellbooks[i].s[j].effect == "death"){
					value = false;
				}
			}
		}
		if(num == 1){
			if(value == true){
				cout << spellbooks[i].title << " " << spellbooks[i].num_pages << endl;
			}
		}else if(num == 1){
			if(value == true){
				cout << spellbooks[i].title << " " << spellbooks[i].avg_success_rate << endl;
			}
		}
		value = true;
	}
}

//Function that prints out to screen (spell effects only). Takes in a spell type, integer, wizard type, and a string. Doesn't return anything
void screen_effect(spell* spells, int total_spells, wizard user, string style_type){
	string word;
	int limit;
	cout << style_type << endl;
	if(user.position_title == "Student"){
		limit = 3;
	}else{
		limit = 5;
	}
	for(int i = 0; i < limit; i++){
		if(i == 0){
			word = "bubble";
		}else if(i == 1){
			word = "memory_loss";
		}else if(i == 2){
			word = "fire";
		}else if(i == 3){
			word = "poison";
		}else if(i == 4){
			word = "death";
		}
		for(int j = 0; j < total_spells; j++){
			if(spells[j].effect == word){
				cout << spells[j].name << " " << spells[j].effect << endl;
			}
		}
	}
}

//Function that pritns out to a file (spell effects only). Takes in a spell type, integer, wizard type, string, and a file. Doesn't return anything
void file_effect(spell* spells, int total_spells, wizard user, string style_type, fstream &file){
	string new_file;
	cout << "What file do you want to write to?: " << endl;
	cin >> new_file;
	file.open(new_file.c_str(), ios::out | ios::app);

	string word;
	int limit;
	file << style_type << endl;
	if(user.position_title == "Student"){
		limit = 3;
	}else{
		limit = 5;
	}
	for(int i = 0; i < limit; i++){
		if(i == 0){
			word = "bubble";
		}else if(i == 1){
			word = "memory_loss";
		}else if(i == 2){
			word = "fire";
		}else if(i == 3){
			word = "poison";
		}else if(i == 4){
			word = "death";
		}
		for(int j = 0; j < total_spells; j++){
			if(spells[j].effect == word){
				file << spells[j].name << " " << spells[j].effect << endl;
			}
		}
	}
	file.close();
}

//Function that sorts all the spells by effect type. Takes in a spellbook type, wizard type, integer, and a file
void sort_by_spell_effect(spellbook* spellbooks, wizard user, int number_of_books, fstream &file){
	int total_spells;
	int size = 0;
	for(int i = 0; i < number_of_books; i++){
		total_spells = total_spells + (spellbooks[i].num_spells);
	}
	spell* spell_effect_list = new spell[total_spells];
	for(int j = 0; j < number_of_books; j++){
		for(int k = 0; k < spellbooks[j].num_spells; k++){
			if(size < total_spells){
				spell_effect_list[size++] = (spellbooks[j].s[k]);
			}
		}
	}

	bool value;
	do{
		int number = get_int("Do you want to print to screen(1), or write to file(2)?: ");
		if(number == 1){
			screen_effect(spell_effect_list, total_spells, user, "Sort by Spell Effect: ");
			value = true;
		}else if(number == 2){
			file_effect(spell_effect_list, total_spells, user, "Sort by Spell Effect: ", file);
			value = true;
		}else{
			cout << "Invalid option." << endl;
			value = false;
		}
	}while(value == false);
	delete [] spell_effect_list;
}

//Function that sorts spellbooks by average success rate. Takes in a spellbook type, wizrd type, integer, and a file. Doesn't return anything
void sort_by_avg_success(spellbook* spellbooks, wizard user, int number_of_books, fstream &file){
	int num;
	spellbook* avg_rate_list = new spellbook[number_of_books];
	for(int i = 0; i < number_of_books; i++){
		for(int j = 0; j < number_of_books; j++){
			if(spellbooks[i].avg_success_rate < spellbooks[j].avg_success_rate){
				num++;
			}
		}
		avg_rate_list[num - num - 1] = spellbooks[i];
		num = 0;
	}
	bool value;
	do{
		int number = get_int("Do you want to print to screen(1), or write to file(2)?: ");
		if(number == 1){
			screen_print(avg_rate_list, 2, number_of_books, user, "Sort by Average Success Rate: ");
			value = true;
		}else if(number == 2){
			file_print(avg_rate_list, 2, number_of_books, user, "Sort by Average Success Rate: ", file);
			value = true;
		}else{
			cout << "Invalid option." << endl;
			value = false;
		}
	}while(value == false);
	delete [] avg_rate_list;	
}


//Function that sorts spellbook sby page number. Takes in a spellbook type, wizard type, integer, and a file. Doesn't return aything
void sort_by_page_num(spellbook* spellbooks, wizard user, int number_of_books, fstream &file){
	int num;
	spellbook* page_num_list = new spellbook[number_of_books];
	for(int i = 0; i < number_of_books; i++){
		for(int j= 0; j < number_of_books; j++){
			if(spellbooks[i].num_pages < spellbooks[j].num_pages){
				num++;
			}
		}
		page_num_list[number_of_books - num - 1] = spellbooks[i];
		num = 0;
	}
	bool value;
	do{
		int number = get_int("Do you want to print the info to screen(1), or write to file(2)?: ");
		if(number == 1){
			screen_print(page_num_list, 1, number_of_books, user, "Sort by Page Number: ");
			value = true;
		}else if(number == 2){
			file_print(page_num_list, 1, number_of_books, user, "Sort By Page Number: ", file);
			value = true;
		}else{
			cout << "Invalid option." << endl;
			value = false;
		}
	}while(value = false);
	delete [] page_num_list;
}
