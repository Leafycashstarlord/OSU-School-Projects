/*************
 * Header file for deck.h
 * Author: Jackson E. Rollins
 * *************/

#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "card.h"

using namespace std;

//Class Deck
class Deck{
	private:
		Card cards[52];
		int n_cards;
	public:
		Deck();
		Card* get_cards();
		int get_n_cards();
		void shuffle_deck();
		void print_deck();
		int myrandom(int i);
};

#endif
