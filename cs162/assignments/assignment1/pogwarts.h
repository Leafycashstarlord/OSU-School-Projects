/****************
 *Author: Jackson E. Rollins
 * *****************/
#ifndef POGWARTS_H
#define POGWARTS_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

//Structre defining the wizard type
struct wizard{
	string name;
	int id;
	string password;
	string position_title;
	float beard_length;
};

//Structure defining the spellbook type
struct spellbook{
	string title;
	string author;
	int num_pages;
	int edition;
	int num_spells;
	float avg_success_rate;
	struct spell *s;
};

//Structure defining the spell type
struct spell{
	string name;
	float success_rate;
	string effect;
};

//All the Function declarations
spellbook* create_spellbooks(int);

void get_spellbook_data(spellbook* , int, ifstream &);

spell* create_spells(int);

void get_spell_data(spell *, int, ifstream &);

void delete_info(spellbook *, int);

int get_book_number(char **, fstream &);

int get_int(string);

int get_wizard_db(char **, wizard* &, fstream &);

bool login(char **, wizard &, fstream &);

bool search_wizard_db(wizard *, int, int, string, wizard &);

void sort_books(spellbook *, wizard, int, fstream &);

void file_print(spellbook *, int, int, wizard, string, fstream &);

void screen_print(spellbook *, int, int, wizard, string);

void screen_effect(spell *,  int, wizard, string);

void file_effect(spell *, int, wizard, string, fstream &);

void sort_by_page_num(spellbook *, wizard , int, fstream &);

void sort_by_spell_effect(spellbook *, wizard , int, fstream &);

void sort_by_avg_success(spellbook *, wizard , int, fstream &);

#endif
