/*******
 * Header file for card.h
 * Author: Jackson E. Rollins
 * ******/

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

//Class card
class Card{
	private:
		int suit;
		int rank;
	public:
		Card();
		void set_card_rank(int);
		void set_card_suit(int);
		int get_rank(void);
		int get_suit(void);
		void print_card();
};

#endif
