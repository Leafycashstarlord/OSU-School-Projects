/*******
 *Jackson E. Rollins
 *5/25/2020
 *Event header file
 * *******/
#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>

using namespace std;

//Event class
class Event{
	protected:
		string warning_msg = "";
	public:
		virtual string get_warning() = 0;
};

#endif
