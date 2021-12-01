/*************
 *Implementation file for Game.cpp
 *Author: Jackson E. Rollins
 **************/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "get_int.h"
#include "player.h"
#include "game.h"

using namespace std;

//Default COnstructor for Game type
Game::Game(){
	players[0].set_name("User");
	players[1].set_name("Computer");
}


//Function that starts the game, deals out each players hand and brings
//out a top card for the pile
void Game::start_game(){

}

//Function that plays the game, alternating between players turns
void Game::play_game(){

}

//Function that checks to see whether or not the game has ended
bool Game::game_over(){

}

//Function that checks to see is a users hand is empty
bool out_of_cards_hand(Hand& hand){
	bool value = true;
	for(int i = 0; i < hand.get_n_cards(); i++){
		if(hand.get_cards()[i].get_rank() != NULL){
			value = false;
		}
	}
	return value;
}

//Function that checks to see is the draw deck is empty
bool out_of_cards_deck(Deck& cards){
	bool value = true;
	for(int i = 0; i < 52; i++){
		if(cards.get_cards()[i].get_rank() != NULL){
			value = false;
		}
	}
	return value;
}
