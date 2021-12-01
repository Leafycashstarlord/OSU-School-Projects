/***************
 * Program: crazy8_driver.cpp
 * Author: Jackson E. Rollins
 * Date: 4/26/2020
 * Description: Play the card game crazy eights
 * Input: None
 * Output: None
 * **************/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "hand.h"
#include "card.h"
#include "deck.h"
#include "get_int.h"
#include "player.h"
#include "game.h"

using namespace std;

//Main Function that does everything
int main(){
	srand(time(NULL));
	Deck my_deck;
	Hand my_hand;
	Hand cpu_hand;

	for(int i = 0; i < 7; i++){
		my_hand.draw_card(my_deck, my_hand);
	}
	for(int j = 0; j < 7; j++){
		cpu_hand.draw_card(my_deck, cpu_hand);
	}
	cout << "User's Hand: " << endl;
	my_hand.print_hand();
	cout << "Computer's Hand: " << endl;
	cpu_hand.print_hand();

	return 0;
	
}
