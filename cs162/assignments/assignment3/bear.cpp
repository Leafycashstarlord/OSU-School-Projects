/******************
 *Program: bear.cpp
 *Authoer: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Implementation file for the bear class
 * **************/
#include <iostream>
#include <string>
#include "bear.h"
#include "animal.h"

using namespace std;

//Default constructor for the bear class
Bear::Bear(){
	name = "Bear";
	age = 0;
	animal_cost = 0;
	babies = 0;
	food_cost = 0;
	revenue = 0;
}

//Custom Constructor for the bear class
Bear::Bear(string new_name, int new_age, int new_animal_cost, int new_babies, int new_food_cost, int new_revenue){
	name = new_name;
	age = new_age;
	animal_cost = new_animal_cost;
	babies = new_babies;
	food_cost = new_food_cost;
	revenue = new_revenue;
}
