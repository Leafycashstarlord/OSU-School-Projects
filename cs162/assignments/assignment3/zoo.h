/************
 *Program: zoo.h
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: zoo header file
 * ************/
#ifndef ZOO_H
#define ZOO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "animal.h"
#include "tiger.h"
#include "bear.h"
#include "sealion.h"
#include "get_int.h"

using namespace std;

//Zoo class
class Zoo{
	private:
		Sealion* seals;
		int seal_num;
		Tiger* tigers;
		int tiger_num;
		Bear* bears;
		int bear_num;
		float food_price;
		int month;
		int money;
	public:
		Zoo();
		~Zoo();
		Sealion* get_seals();
		Tiger* get_tigers();
		Bear*  get_bears();
		void play_game();
		void age_up();
		void random_event();
		void sickness();
		void kill_seal(int);
		void kill_tiger(int);
		void kill_bear(int);
		void birth();
		void birth_seals();
		void birth_tigers();
		void birth_bears();
		void monthly_paycheck();
		void animal_purchase();
		void monthly_feeding();
		void set_money(int);
		int get_money();
		void set_month(int);
		int get_month();
		void set_food_price(float);
		float get_food_price();
		void set_seal_num(int);
		int get_seal_num();
		void set_tiger_num(int);
		int get_tiger_num();
		void set_bear_num(int);
		int get_bear_num();
};

#endif
