/*******************
 * Implmentation file for Player.cpp
 * Authoer: Jackson E. Rollins
 * ****************/

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

using namespace std;

//Default constructor for player class
Player::Player(){
	name = "";
}

//Function that gets the name of the player
string Player::get_name(){
	return name;
}

//Function that sets the name of the player
void Player::set_name(string new_name){
	name = new_name;
}

//Function that gets the hand of the player
Hand Player::get_hand(){
	return hand;
}

//Function that sets the hand of the player
void Player::set_hand(Hand& new_hand){
	hand = new_hand;
}
