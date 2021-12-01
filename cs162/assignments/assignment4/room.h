/*********
 *Jackson E. ROllins
 *5/25/2020
 *Room header file
 * *********/
#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "bats.h"
#include "gold.h"
#include "wumpus.h"
#include "pit.h"
#include "event.h"
#include "empty.h"

using namespace std;

//Room class
class Room{
	protected:
		int event_num;
		bool player;
		Event* eptr;
	public:
		Room();
		~Room();
		int get_event_num();
		bool get_player();
		string get_event_warning();
		void set_player(bool);
		void set_event_num(int);
		void delete_event();
		void set_event(int);
		
		
};

#endif
