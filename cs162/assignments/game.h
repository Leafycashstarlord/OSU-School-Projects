/***********
 * Header file for Game.h
 * Authoer: Jackson E. ROllins
 * ************/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "get_int.h"
#include "player.h"

using namespace std;

//Class game
class Game{
	private:
		Deck cards;
		Player players[2];
	public:
		Game();
		void start_game();
		void play_game();
		bool game_over();
		bool out_of_cards_hand();
		bool out_of_cards_deck();
};

#endif
