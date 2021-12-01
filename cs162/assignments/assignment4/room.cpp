/***********
 *Jackson E. Rollins
 *5/25/2020
 *Room class cpp file
 * *********/

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "bats.h"
#include "gold.h"
#include "wumpus.h"
#include "pit.h"
#include "room.h"
#include "event.h"
#include "empty.h"

using namespace std;

//Room constructor
Room::Room(){
	event_num = 0;
	player = false;
}

//Room deconstructor
Room::~Room(){
	delete [] eptr;
}

//Get event_num
int Room::get_event_num(){
	return event_num;
}

//Set event_num
void Room::set_event_num(int num){
	event_num = num;
}

//Get player
bool Room::get_player(){
	return player;
}

//Set player
void Room::set_player(bool x){
	if(x == true){
		player = true;
	}else if(x == false){
		player = false;
	}
}

//Set the event
void Room::set_event(int num){
	if(num == 2){
		eptr = new Wumpus;
	}else if(num = 3){
		eptr = new Gold;
	}else if(num = 4){
		eptr = new Pit;
	}else if(num = 5){
		eptr = new Bats;
	}else{
		eptr = new Empty;
	}
}

//Delete event pointer
void Room::delete_event(){
	delete [] eptr;
	Event *ptr;
}

//Get event warning
string Room::get_event_warning(){
	string msg = eptr->get_warning();
	return msg;
}
