/***************
 *Jackson E. Rollins
 *5/25/2020
 *Bats header file
 * **************/
#ifndef BATS_H
#define BATS_H

#include <iostream>
#include <string>
#include "event.h"

using namespace std;

//Bats class
class Bats : public Event{
	protected:
		string warning_msg;
	public:
		Bats();
		string get_warning();
};

#endif
