/**********
 * Header file for hand.h
 * Author: Jackson E. Rollins
 * ********/
#ifndef HAND_H
#define HAND_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "card.h"
#include "deck.h"
#include "get_int.h"

using namespace std;

class Hand{
	private:
		int n_cards;
		Card* cards;
		
	public:
		Hand();
		Hand(int);
		~Hand();
		Hand(const Hand&);
		Hand& operator=(const Hand&);
		void print_hand();

		Card* get_cards();
		int get_n_cards();
		void set_n_cards(int);
		void draw_card(Deck&, Hand&);
		
};

#endif
