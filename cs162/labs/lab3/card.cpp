#include <iostream>
#include <string>
#include "card.h"

using namespace std;

Card::Card(): suit("") rank(0){}

void Card::set_card_rank(int rank){
	this->rank = rank'
}

int Card::get_rank(){
	return this->rank;
}

void Card::set_card_suit(string suit){
	this->suit = suit;
}

string Card::get_suit(){
	return this->suit;
}
