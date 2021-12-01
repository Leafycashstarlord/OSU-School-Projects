#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "card.h"
#include "deck.h"

using namespace std;

Deck::get_deck(){
	shuffle();
}

void Deck::shuffle_deck(){
	int num;
	int value;
	for(int i = 0; i < 52; i++){
		num = rand()%13
		value = rand()%4
		if(i == 0){
			cards[i].set_card_rank(num + 1);
			if(value == 0){
				cards[i].set_card_suit("Hearts");
			}else if(value == 1){
				cards[i].set_card_suit("Diamonds");
			}else
		}
	}
}	

Cards* Deck::get_cards(){
	return cards;
}

void Deck::print_deck(){
	for(int i = 0; i < 52; i++){
		if(cards[i].get_rank() == 1){
			cout << "Ace";
		}else if(cards[i].get_rank() == 11){
			cout << "Jack";
		}else if(cards[i].get_rank() == 12){
			cout << "Queen";
		}else if(cards[i].get_rank() == 13){
			cout << "King";
		}else{
			cout << cards[i].get_rank();
		}
		cout << " " << cards[i].get_suit() << endl;
	}
}
