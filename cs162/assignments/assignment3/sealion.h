/************
 *Program: sealion.h
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Header file for my sealion class
 * **********/
#ifndef SEALION_H
#define SEALION_H

#include <iostream>
#include <string>
#include "animal.h"

using namespace std;

//Sealion class
class Sealion : public Animal{
	private:
		int bonus_payout;
	public:
		Sealion();
		Sealion(string, int, int, int, int, int);
		int get_bonus_payout();
		void set_bonus_payout(int);
};

#endif
