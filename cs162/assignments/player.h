/***********
 * Header file for Player.h
 * Authoer: Jackson E. Rollins
 * **********/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "get_int.h"

using namespace std;
//Class Player
class Player{
	private:
		Hand hand;
		string name;
	public:
		Player();
		string get_name();
		void set_name(string);
		Hand get_hand();
		void set_hand(Hand&);
};

#endif
