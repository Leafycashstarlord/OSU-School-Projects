/*********
 *Jackson E. Rollins
 *5/25/2020
 *Empty header file
 * *********/
#ifndef EMPTY_H
#define EMPTY_H

#include <iostream>
#include <string>
#include "event.h"

using namespace std;

//Empty class
class Empty : public Event{
	protected:
		string warning_msg;
	public:
		Empty();
		string get_warning();
};

#endif
