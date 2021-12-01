/****************
 *Program: zoo.cpp
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Implementation file fo rmy zoo class
 * *************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "animal.h"
#include "tiger.h"
#include "bear.h"
#include "sealion.h"
#include "zoo.h"
#include "get_int.h"

using namespace std;

//Default constructor
Zoo::Zoo(){
	seal_num = 0;
	tiger_num = 0;
	bear_num = 0;
	food_price = 80;
	month = 0;
	money = 100000;
	seals = new Sealion[0];
	tigers = new Tiger[0];
	bears = new Bear[0];
}

//Deconstructor
Zoo::~Zoo(){
	delete [] seals;
	delete [] tigers;
	delete [] bears;
}

//Gets the sea lion array
Sealion* Zoo::get_seals(){
	return seals;
}

//Gets the tiger array
Tiger* Zoo::get_tigers(){
	return tigers;
}

//Gets the bear array
Bear* Zoo::get_bears(){
	return bears;
}

//Function that plays an entire turn for the game
//If its the first turn, welcomes the user, and asks them for animals to buy, and food to buy if an animal is bought
//Any other turn prints out the total money, food price, and amounts of babies/adults that you have for the month
//Also runs the age up, random event, monthly paycheck, animal purchase, and food purchase functions
void Zoo::play_game(){
	if(month == 0){
		cout << "Welcome to Zoo Tycoon!" << endl;
		cout << "The game where you create and manage your very own Zoo!" << endl;
		cout << "This is the first month: you start with $100,000, and the price of food is $80!" << endl;
		animal_purchase();
		monthly_feeding();
	}else{
		int baby = 0;
		int adult = 0;
		cout << "Month: " << (month + 1) << endl;
		for(int i = 0; i < seal_num; i++){
			if(seals[i].get_age() < 7){
				baby++;
			}else if(seals[i].get_age() > 47){
				adult++;
			}
		}
		cout << "Adult Seals: " << adult << endl;
		cout << "Baby Seals: " << baby << endl;
		baby = 0;
		adult = 0;
		for(int j = 0; j < tiger_num; j++){
			if(tigers[j].get_age() < 7){
				baby++;
			}else if(tigers[j].get_age() > 47){
				adult++;
			}
		}
		cout << "Adult Tigers: " << adult << endl;
		cout << "Baby Tigers: " << baby << endl;
		baby = 0;
		adult = 0;
		for(int k = 0; k < bear_num; k++){
			if(bears[k].get_age() < 7){
				baby++;
			}else if(bears[k].get_age() > 47){
				adult++;
			}
		}
		cout << "Adult Bears: " << adult << endl;
		cout << "Baby Bears: " << baby << endl;
		baby = 0;
		adult = 0;

		age_up();
		random_event();
		monthly_paycheck();
		cout << "Total Money: " << money << endl;
		cout << "Price of Food: " << food_price << endl;
		animal_purchase();
		monthly_feeding();
	}
	month++;
}

//Function that increases the age of all animals in the zoo by 1 month, changing their status if they get older than that of a child (6 months)
void Zoo::age_up(){
	if(seal_num + tiger_num + bear_num > 0){
		cout << "Your Animals Got Older!" << endl;
		if(seal_num > 0){
			for(int i = 0; i < seal_num; i++){
				seals[i].set_age((seals[i].get_age()) + 1);
				if(seals[i].get_age() > 6){
					seals[i].set_revenue(160);
				}
				seals[i].set_bonus_payout(0);
			}
		}

		if(tiger_num > 0){
			for(int j = 0; j < tiger_num; j++){
				tigers[j].set_age((tigers[j].get_age()) + 1);
				if(tigers[j].get_age() > 6){
					tigers[j].set_revenue(1500);
				}	
			}
		}

		if(bear_num > 0){
			for(int k = 0; k < bear_num; k++){
				bears[k].set_age((bears[k].get_age()) + 1);
				if(bears[k].get_age() > 6){
					bears[k].set_revenue(600);
				}
			}
		}
	}
}

//Random event function, randomly chooses an event to happen every turn
//Nothing happens, Animal gives birth, Animal gets sick, or Zoo gets crowded increasing sea lion revenue
void Zoo::random_event(){
	if((seal_num + tiger_num + bear_num) > 0){
		int number = rand() % 4;
		if(number == 1){
			sickness();
		}else if(number == 2){
			birth();
		}else if(number == 3){
			if(seal_num > 0){
				cout << "It's a crowded day a the Zoo!" << endl;
				cout << "(Sea Lions Generate Extra $$)" << endl;
				for(int i = 0; i < seal_num; i++){
					seals[i].set_bonus_payout((rand() % 251)+150);
				}
			}
		}
	}
}

//Function that arranges for the sickness event
//A random animal gets sick, and the user eithe rhas to pay to cure it if they have the money, or let it die
void Zoo::sickness(){
	int number = rand() % 3;
	int sick_cost;
	if(number == 0){
		if(seal_num > 0){
			cout << "One of your Seals Got Sick!" << endl;
			int seal = rand() % seal_num;
			if(seals[seal].get_age() < 7){
				sick_cost = 800;
			}else{
				sick_cost = 400;
			}
			if(money > sick_cost){
				cout << "You bought Medicine!" << endl;
				cout << "The Animal Survived!" << endl;
				money = money - sick_cost;
			}else{
				cout << "You Couldn't Buy Medicine!" << endl;
				cout << "The Animal Died!" << endl;
				kill_seal(seal);
			}
		}
	}else if(number == 1){
		if(tiger_num > 0){
			cout << "One of your Tigers got Sick!" << endl;
			int tiger = rand() % tiger_num;
			if(tigers[tiger].get_age() < 7){
				sick_cost = 15000;
			}else{
				sick_cost = 7500;
			}
			if(money > sick_cost){
				cout << "You Bought Medicine!" << endl;
				cout << "The Animal Survived!" << endl;
				money = money - sick_cost;
			}else{
				cout << "You Couldn't Buy Medicine!" << endl;
				cout << "The Animal Died!" << endl;
				kill_tiger(tiger);
			}
		}
	}else if(number == 2){
		if(bear_num > 0){
			cout << "One of your Bears got Sick!" << endl;
			int bear = rand() % bear_num;
			if(bears[bear].get_age() < 7){
				sick_cost = 6000;
			}else{
				sick_cost = 3000;
			}
			if(money > sick_cost){
				cout << "You Bought Medicine!" << endl;
				cout << "The Animal Survived!" << endl;
				money = money - sick_cost;
			}else{
				cout << "You Couldn't Buy Medicine!" << endl;
				cout << "The Animal Died!" << endl;
				kill_bear(bear);
			}
		}
	}
}

//Function that kills a seal, removing it from the array
void Zoo::kill_seal(int seal){
	Sealion* temp_array = new Sealion[seal_num];
	for(int i = 0; i < seal_num; i++){
		temp_array[i] = seals[i];
	}
	delete [] seals;
	seal_num--;
	seals = new Sealion[seal_num];
	int vari = 0;
	for(int j = 0; j < seal_num; j++){
		if(j != seal){
			seals[vari] = temp_array[j];
			vari++;
		}
	}
	delete [] temp_array;
}

//Function that kills a tiger, removing it from the array
void Zoo::kill_tiger(int tiger){
	Tiger* temp_array = new Tiger[tiger_num];
	for(int i = 0; i < tiger_num; i++){
		temp_array[i] = tigers[i];
	}
	delete [] tigers;
	tiger_num--;
	tigers = new Tiger[tiger_num];
	int vari = 0;
	for(int j = 0; j < tiger_num; j++){
		if(j != tiger){
			tigers[vari] = temp_array[j];
			vari++;
		}
	}
	delete [] temp_array;
}

//Function that kills a bear, removing it from the array
void Zoo::kill_bear(int bear){
	Bear* temp_array = new Bear[bear_num];
	for(int i = 0; i < bear_num; i++){
		temp_array[i] = bears[i];
	}
	delete [] bears;
	bear_num--;
	bears = new Bear[bear_num];
	int vari = 0;
	for(int j = 0; j < bear_num; j++){
		if(j != bear){
			bears[vari] = temp_array[j];
			vari++;
		}
	}
	delete [] temp_array;
}

//Function that arranges for the birth of any animal
//Randomly picks an adult animal int eh zoo to give birth for the random event
void Zoo::birth(){
	int number = rand() % 3;

	if(number == 0){
		if(seal_num > 0){
			for(int i = 0; i < seal_num; i++){
				if(seals[i].get_age() > 47){
					cout << "The seals gave birth to 1 cub!" << endl;
					birth_seals();
					break;
				}
			}
		}
	}else if(number == 1){
		if(tiger_num > 0){
			for(int j = 0; j < tiger_num; j++){
				if(tigers[j].get_age() > 47){
					cout << "The Tigers gave birth to 3 cubs!" << endl;
					birth_tigers();
					break;
				}
			}
		}
	}else if(number == 2){
		if(bear_num > 0){
			for(int k = 0; k < bear_num; k++){
				if(bears[k].get_age() > 47){
					cout << "The Bears gave birth to 2 cubs!" << endl;
					birth_bears();
					break;
				}
			}
		}
	}
}

//Function that gives birth to a seal, adding it to the array
void Zoo::birth_seals(){
	Sealion* temp_array = new Sealion[seal_num];
	for(int i = 0; i < seal_num; i++){
		temp_array[i] = seals[i];
	}
	delete [] seals;
	seal_num = seal_num + 1;
	seals = new Sealion[seal_num];
	for(int j = 0; j < seal_num; j++){
		if(j < (seal_num - 1)){
			seals[j] = temp_array[j];
		}else if(j == (seal_num -1)){
			seals[j] = Sealion("Sealion", 0, 800, 1, 1, 320);
		}
	}
	delete [] temp_array;
}

//Function that gives birth to a tiger, adding it to the array
void Zoo::birth_tigers(){
	Tiger* temp_array = new Tiger[tiger_num];
	for(int i = 0; i < tiger_num; i++){
		temp_array[i] = tigers[i];
	}
	delete [] tigers;
	tiger_num = tiger_num + 3;
	tigers = new Tiger[tiger_num];
	for(int j = 0; j < tiger_num; j++){
		if(j < (tiger_num - 3)){
			tigers[j] = temp_array[j];
		}else if(j >= tiger_num - 3){
			tigers[j] = Tiger("Tiger", 0, 15000, 3, 5, 3000);
		}
	}
	delete [] temp_array;
}

//Function that gives birth to a bear, adding it to the array
void Zoo::birth_bears(){
	Bear* temp_array = new Bear[bear_num];
	for(int i = 0; i < bear_num; i ++){
		temp_array[i] = bears[i];
	}
	delete [] bears;
	bear_num = bear_num + 2;
	bears = new Bear[bear_num];
	for(int j = 0; j < bear_num; j++){
		if(j < (bear_num - 2)){
			bears[j] = temp_array[j];
		}else if(j >= (bear_num - 2)){
			bears[j] = Bear("Bear", 0, 6000, 2, 3, 1200);
		}
	}
	delete [] temp_array;
}

//Function that calculates the amount of money earned that month, and adds it to the player total
void Zoo::monthly_paycheck(){
	int new_money = 0;
	if((seal_num + tiger_num + bear_num) > 0){
		cout << "Monthly Revenue Is In!" << endl;
		if(seal_num > 0){
			for(int i = 0; i < seal_num; i++){
				new_money = new_money + seals[i].get_revenue() + seals[i].get_bonus_payout();
			}
		}

		if(tiger_num > 0){
			for(int j = 0; j < tiger_num; j++){
				new_money = new_money + tigers[j].get_revenue();
			}
		}

		if(bear_num > 0){
			for(int k = 0; k < bear_num; k++){
				new_money = new_money + bears[k].get_revenue();
			}
		}
	}

	money = money + new_money;
}

//Function used to purchase animals on a users turn
//Choose an animal to buy or none at all, as well as the amount that you would wnat to buy
void Zoo::animal_purchase(){
	int number = get_int("Animal to buy? 1 for Seals, 2 for Tigers, 3 for Bears, or 4 for none: ", 1, 4);
	int amount;
	if(number != 4){
		amount = get_int("Wanna buy 1 or 2?: ", 1, 2);
	}

	if(number == 1){
		Sealion* temp_array = new Sealion[seal_num];
		for(int i = 0; i < seal_num; i++){
			temp_array[i] = seals[i];
		}
		delete [] seals;
		seal_num = seal_num + amount;
		seals = new Sealion[seal_num];
		for(int j = 0; j < seal_num; j++){
			if(j < seal_num - amount){
				seals[j] = temp_array[j];
			}else if(j >= seal_num - amount){
				seals[j] = Sealion("Sealion", 48, 800, 1, 1, 160);
			}
		}
		delete [] temp_array;
		money -= amount*800;
	}else if(number == 2){
		Tiger* temp_array2 = new Tiger[tiger_num];
		for(int k = 0; k < tiger_num; k++){
			temp_array2[k] = tigers[k];
		}
		delete [] tigers;
		tiger_num = tiger_num + amount;
		tigers = new Tiger[tiger_num];
		for(int t = 0; t < tiger_num; t++){
			if(t < tiger_num - amount){
				tigers[t] = temp_array2[t];
			}else if(t >= tiger_num - amount){
				tigers[t] = Tiger("Tiger", 48, 15000, 3, 5, 1500);
			}
		}
		delete [] temp_array2;
		money -= amount*15000;
	}else if(number == 3){
		Bear* temp_array3 = new Bear[bear_num];
		for(int y = 0; y < bear_num; y++){
			temp_array3[y] = bears[y];
		}
		delete [] bears;
		bear_num = bear_num + amount;
		bears = new Bear[bear_num];
		for(int x = 0; x < bear_num; x++){
			if(x < bear_num - amount){
				bears[x] = temp_array3[x];
			}else if(x >= bear_num -amount){
				bears[x] = Bear("Bear", 48, 6000, 2, 3, 600);
			}
		}
		delete [] temp_array3;
		money -= amount*6000;
	}
}

//Calculates the amoutn of money it takes to feed all the animals, and subtracts it form the total
//Also calculates the next month's base food cost
void Zoo::monthly_feeding(){	
	int total_feed = 0;
	if((seal_num + tiger_num + bear_num) > 0){
		cout << "Time To Buy Animal Feed!" << endl;
		total_feed = (seal_num * food_price) + (tiger_num * food_price * 5) + (bear_num * food_price * 3);
	}

	money = money - total_feed;
	float percent = (((rand() % 41) + 80.0) / 100.0);
	food_price *= percent;
}

//Set the total money the user has
void Zoo::set_money(int new_money){
	money = new_money;
}

//Get the total money the user has
int Zoo::get_money(){
	return money;
}

//set the month
void Zoo::set_month(int new_month){
	month = new_month;
}

//Get the month
int Zoo::get_month(){
	return month;
}

//Set the base cost of food
void Zoo::set_food_price(float new_price){
	food_price = new_price;
}

//The the base cost of food
float Zoo::get_food_price(){
	return food_price;
}

//Set the number of seals
void Zoo::set_seal_num(int num){
	seal_num = num;
}

//Get the number the seals
int Zoo::get_seal_num(){
	return seal_num;
}

//Set the numbe rof tigers
void Zoo::set_tiger_num(int num){
	tiger_num = num;
}

//Get the number of tigers
int Zoo::get_tiger_num(){
	return tiger_num;
}

//Set the numbe rof bears
void Zoo::set_bear_num(int num){
	bear_num = num;
}

//Get the number o fbears
int Zoo::get_bear_num(){
	return bear_num;
}
