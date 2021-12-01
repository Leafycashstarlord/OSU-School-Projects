/************
 *Jackosn E. Rollins
 *5/25/2020
 *Pit header file
 * ************/
#ifndef PIT_H
#define PIT_H

#include <iostream>
#include <string>
#include "event.h"

using namespace std;

//Pit class
class Pit : public Event{
	protected:
		string msg;
	public:
		Pit();
		string get_warning();
};

#endif
