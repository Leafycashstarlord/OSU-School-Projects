/*********
 * Implementation file for card.cpp
 * Author: Jackson E. Rollins
 * **********/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "card.h"

using namespace std;

//Default card constructor
Card::Card(){
	suit = 4; 
	rank = 0;
}

//Function that sets the card rank
void Card::set_card_rank(int new_rank){
	rank = new_rank;
}

//Function that sets the card suit
void Card::set_card_suit(int new_suit){
	suit = new_suit;
}

//Function that gets the card rank
int Card::get_rank(){
	return rank;
}


//Function that gets the card suit
int Card::get_suit(){
	return suit;
}

//Function that prints the card out
void Card::print_card(){
	if(rank == 1){
		cout << "Ace";
	}else if(rank == 11){
		cout << "Jack";
	}else if(rank == 12){
		cout << "Queen";
	}else if(rank == 13){
		cout << "King";
	}else{
		cout << rank;
	}
	cout <<  " of ";
	if(suit == 0){
		cout << "Spades" << endl;
	}else if(suit == 1){
		cout << "Hearts" << endl;
	}else if(suit == 2){
		cout << "Diamonds" << endl;
	}else if(suit == 3){
		cout << "Clubs" << endl;
	}
}
