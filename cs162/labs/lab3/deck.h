#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "card.h"

using namespace std;

class Deck {
private:
	Card cards[52];
public:
	get_deck();
	Cards* get_cards();
	void shuffle_deck();
	void print_deck();
}


#endif
