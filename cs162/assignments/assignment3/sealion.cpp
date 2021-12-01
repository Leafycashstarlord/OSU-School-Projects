/**************
 *Program: sealion.cpp
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Implementation file for the sealion class
 * ***************/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "animal.h"
#include "sealion.h"

using namespace std;

//Default Constructor
Sealion::Sealion(){
	name = "Sealion";
	age = 0;
	animal_cost = 0;
	babies = 0;
	food_cost = 0;
	revenue = 0;
	bonus_payout = 0;
}

//Custom Constructor
Sealion::Sealion(string new_name, int new_age, int new_animal_cost, int new_babies, int new_food_cost, int new_revenue){
	name = new_name;
	age = new_age;
	animal_cost = new_animal_cost;
	babies = new_babies;
	food_cost = new_food_cost;
	revenue = new_revenue;
	bonus_payout = 0;
}

//Get the seal's bonus payout
int Sealion::get_bonus_payout(){
	return bonus_payout;
}

//Sets the seal's bonus payout
void Sealion::set_bonus_payout(int num){
	bonus_payout = num;
}
