/*************
 * Implementation file for hand.cpp
 * Author: Jackson E. Rollins
 * ************/

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

//Default constructor for hand class
Hand::Hand(){
	n_cards = 52;
	cards  = new Card[n_cards];
	for(int i = 0; i < n_cards; i++){
		cards[i].set_card_rank(NULL);
	}
}

//Custum constructor for hand class
Hand::Hand(int num){
	cards  = new Card[num];
	for(int i = 0; i < num; i++){
		cards[i].set_card_rank(NULL);
	}
	n_cards = num;
}

//Deconstructor for hand class
Hand::~Hand(){
	delete [] cards;
}

//Copy ocnstructor for hand class
Hand::Hand(const Hand &old_hand){
	n_cards = old_hand.n_cards;
	cards = new Card[n_cards];
	for(int i = 0; i < n_cards; i++){
		cards[i] = old_hand.cards[i];
	}
}

//Overload operator for the hand class
Hand& Hand::operator=(const Hand& old_hand){
	if(this != &old_hand){
		//delete [] cards;
		n_cards = old_hand.n_cards;
		for(int i = 0; i < n_cards; i++){
			cards[i] = old_hand.cards[i];
		}
	}
	return *this;
}

//Function that prints out a players hand
void Hand::print_hand(){
	for(int i = 0; i < n_cards; i++){
		if(cards[i].get_rank() != NULL){
			cards[i].print_card();
		}
	}
}

//Function that gets the number of cards in a players hand
int Hand::get_n_cards(){
	return n_cards;
}

//Function that gets the cards in a players hand
Card* Hand::get_cards(){
	return cards;
}

//Function that sets the number of cards in a players hand
void Hand::set_n_cards(int num){
	n_cards = num;
}

//Function that draws a card to a players hand
void Hand::draw_card(Deck& deck, Hand& hand){
	for(int i = 0; i < 52; i++){
		if(deck.get_cards()[i].get_rank() != NULL){
			cards[i] = deck.get_cards()[i];
			deck.get_cards()[i].set_card_rank(NULL);
			break;
		}
	}
}
