#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namepsace std;

class Card {
private:
	string suit;
	int rank;
public:
	Card();
	void set_card_rank(int);
	void set_card_suit(string);
	int get_rank(void);
	string get_suit(void);
	
};


#endif
