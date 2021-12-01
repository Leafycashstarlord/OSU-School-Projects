/************
 *Jackson E. Rollins
 *5/25/2020
 *Gold header file
 * ************/
#ifndef GOLD_H
#define GOLD_H

#include <iostream>
#include <string>
#include "event.h"

using namespace std;

//Gold class
class Gold : public Event{
	protected:
		string warning_msg;
	public:
		Gold();
		string get_warning();
};

#endif
