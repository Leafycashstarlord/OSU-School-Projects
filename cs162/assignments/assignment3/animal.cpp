/***************
 *Program: animal.cpp
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Implementation file for my animal class
 * ************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "animal.h"

using namespace std;

//Default constructor
Animal::Animal(){
	name = "";
	age = 0;
	animal_cost = 0;
	babies = 0;
	food_cost = 0;
	revenue = 0;
}

//Custom constructor
Animal::Animal(string new_name, int new_age, int new_animal_cost, int new_babies, int new_food_cost, int new_revenue){
	name = new_name;
	age = new_age;
	animal_cost = new_animal_cost;
	babies = new_babies;
	food_cost = new_food_cost;
	revenue = new_revenue;
}

//Gets the animal name
string Animal::get_name(){
	 return name;
}

//Sets the animal name
void Animal::set_name(string new_name){
	name = new_name;
}

//Gets the animal age
int Animal::get_age(){
	return age;
}

//Sets the animal age
void Animal::set_age(int new_age){
	age = new_age;
}

//Gets the animals babies
int Animal::get_babies(){
	return babies;
}

//Sets the animals babies
void Animal::set_babies(int new_babies){
	babies = new_babies;
}

//Gets the animals cost
int Animal::get_animal_cost(){
	return animal_cost;
}

//Sets the animals cost
void Animal::set_animal_cost(int new_animal_cost){
	animal_cost = new_animal_cost;
}

//Gets the animals food cost multiplier
int Animal::get_food_cost(){
	return food_cost;
}

//Sets the animals food cost multiplier
void Animal::set_food_cost(int new_food_cost){
	food_cost = new_food_cost;
}

//Gets the animals revenue
int Animal::get_revenue(){
	return revenue;
}

//Sets the animals revenue
void Animal::set_revenue(int new_revenue){
	revenue = new_revenue;
}
