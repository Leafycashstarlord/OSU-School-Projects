/*******************
 *Program: animal.h
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Header file fo rmy animal class
 * ****************/
#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>

using namespace std;

//Animal class
class Animal{
	public:
		Animal();
		Animal(string, int, int, int, int, int);
		string get_name();
		void set_name(string);
		int get_age();
		void set_age(int);
		int get_babies();
		void set_babies(int);
		int get_animal_cost();
		void set_animal_cost(int);
		int get_food_cost();
		void set_food_cost(int);
		int get_revenue();
		void set_revenue(int);
	protected:
		int age;
		int animal_cost;
		int babies;
		int food_cost;
		int revenue;
		string name;
};

#endif
