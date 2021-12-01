/*********
 *Jackson E. Rollins
 *5/25/2020
 *Wumpus header file
 * *******/
#ifndef WUMPUS_H
#define WUMPUS_H

#include <iostream>
#include <string>
#include "event.h"

using namespace std;

//Wumpus class
class Wumpus : public Event{
	protected:
		string msg_warning;
	public:
		Wumpus();
		string get_warning();
};

#endif
