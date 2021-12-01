/*************
 * Implementation file for deck.cpp
 * Author: Jackson E. Rollins
 * *************/

#include <iostream>
#include <string>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "card.h"
#include "deck.h"

using namespace std;

//Default deck constructor
Deck::Deck(){
	shuffle_deck();
	n_cards = 52;
}

//Function that makes a random number
int Deck::myrandom(int i){
	return rand() % i;
}

//Function that randomly shuffles the deck
void Deck::shuffle_deck(){
	int number = 1;
	int counter = 0;
	for(int i = 0; i < 52; i++){
		cards[i].set_card_rank(number);
		if(counter == 0){
			cards[i].set_card_suit(0);
		}else if(counter == 1){
			cards[i].set_card_suit(1);
		}else if(counter == 2){
			cards[i].set_card_suit(2);
		}else if(counter = 3){
			cards[i].set_card_suit(3);
		}
		number++;
		if(number == 14){
			number = 1;
			counter++;
		}
	}
	
	for(int i = 1; i < 53; i++){
		random_shuffle(cards, cards + 52);
	}
}

//Function that gets the deck of cards
Card* Deck::get_cards(){
	return cards;
}

//Function that gets the number of cards in the deck
int Deck::get_n_cards(){
	return n_cards;
}

//Function that prints the deck of cards out
void Deck::print_deck(){
	for(int i = 0; i < 52; i++){
		cards[i].print_card();
	}
}
