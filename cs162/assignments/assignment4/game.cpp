/********
 *Jackson E. Rollins
 *5/25/2020
 *Game cpp file
 * ********/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "empty.h"
#include "room.h"
#include "gold.h"
#include "wumpus.h"
#include "pit.h"
#include "bats.h"
#include "event.h"
#include "game.h"

using namespace std;

//Game constructor
Game::Game(int size){
	cave_size = size;
	for(int i = 0; i < cave_size; i++){
		vector<Room*> row;
		for(int k = 0; k < cave_size; k++){
			row.push_back(new Room);
		}
		cave.push_back(row);
	}
}

//Game deconstructor
Game::~Game(){
	delete vector<vector<Room*>>cave;
}

//Print the nearby events
void Game::print_nearby_event(){
	if(playery+1 < cave_size && cave[playery+1][playerx]->get_event_num()>1){
		cout << cave[playery+1][playerx]->get_event_warning() << endl;
	}
	if(playerx+1 < cave_size && cave[playery][playerx+1]->get_event_num()>1){
		cout << cave[playery][playerx+1]->get_event_warning() << endl;
	}
	if(playerx-1>=0 && cave[playery][playerx-1]->get_event_num()>1){
		cout << cave[playery][playerx-1]->get_event_warning() << endl;
	}
	if(playery-1>=0 && cave[playery-1][playerx]->get_event_num()>1){
		cout << cave[playery-1][playerx]->get_event_warning() << endl;
	}
}

//Prints the board
void Game::print_board(){
	for(int i = 0; i < cave_size; i++){
		for(int k = 0; k < cave_size; k++){
			cout << cave[i][k]->get_event_num() << " | ";
		}
		cout << endl;
	}
}

//Sets up the board
void Game::set_board(){
	int x;
	int y;
	for(int i = 0; i < 4; i++){
		bool placed = false;
		while(placed == false){
			x = rand()%cave_size;
			y = rand()%cave_size;
			if(cave[y][x]->get_event_num() == 0){
				cave[y][x]->set_event_num(i);
				placed = true;
			}
		}
	}
	for(int k = 0; k < 2; k++){
		int placed = false;
		while(placed == false){
			x = rand()%cave_size;
			y = rand()%cave_size;
			if(cave[y][x]->get_event_num() == 0){
				cave[y][x]->set_event_num(4);
				placed = true;
			}
		}
	}
	for(int j = 0; j < 2; j++){
		int placed = false;
		while(placed == false){
			x = rand()%cave_size;
			y = rand()%cave_size;
			if(cave[y][x]->get_event_num() == 0){
				cave[y][x]->set_event_num(5);
				placed = true;
			}
		}
	}
	for(int l = 0; l < cave_size; l++){
		for(int u = 0; u < cave_size; u++){
			if(cave[l][u]->get_event_num() == 1){
				startx = u;
				starty = l;
				playerx = u;
				playery = l;
				cave[playery][playerx]->set_player(true);
			}
			else if(cave[l][u]->get_event_num() == 2){
				cave[l][u]->set_event(2);
				wumpusx = u;
				wumpusy = l;
				startwx = u;
				startwy = l;
			}
			else if(cave[l][u]->get_event_num() == 3){
				cave[l][u]->set_event(3);
			}
			else if(cave[l][u]->get_event_num() == 4){
				cave[l][u]->set_event(4);
			}
			else if(cave[l][u]->get_event_num() == 5){
				cave[l][u]->set_event(5);
			}
			else{
				cave[l][u]->set_event(0);
			}
		}
	}
}

//Print out the board
void Game::print_player_board(){
	for(int i = 0; i < cave_size; i++){
		for(int k = 0; k < cave_size; k++){
			if(cave[i][k]->get_player() == 0){
				cout << " ";
			}
			else if(cave[i][k]->get_player() == 1){
				cout << "X";
			}
			cout << " | ";
		}
		cout << endl;
	}
}

//Move the player
void Game::move_player(int direction){
	if(direction == 1 && (playery-1)>=0){
		cave[playery][playerx]->set_player(false);
		playery = playery-1;
		cave[playery][playerx]->set_player(true);
	}
	else if(direction == 2 && (playery+1)<cave_size){
		cave[playery][playerx]->set_player(false);
		playery = playery + 1;
		cave[playery][playerx]->set_player(true);
	}
	else if(direction == 3 && (playerx-1)>=0){
		cave[playery][playerx]->set_player(false);
		playerx = playerx - 1;
		cave[playery][playerx]->set_player(true);
	}
	else if(direction == 4 && (playerx+1)<cave_size){
		cave[playery][playerx]->set_player(false);
		playerx = playerx + 1;
		cave[playery][playerx]->set_player(true);
	}
	else{
		cout << "Out of Range!" << endl;
	}
}

//Shoots an arrow
void Game::shoot_arrow(int direction){
	arrowx = playerx;
	arrowy = playery;
	for(int i = 0; i < 3; i++){
		if(direction == 1 && (arrowy-1)>=0 && wumpus == false){
			cout << "Shoot North" << endl;
			arrowy = arrowy - 1;
		}
		else if(direction == 2 && (arrowy+1)<cave_size && wumpus == false){
			cout << "Shoot South" << endl;
			arrowy = arrowy + 1;
		}
		else if(direction == 3 && (arrowx-1)>=0 && wumpus == false){
			cout << "Shoot West" << endl;
			arrowx = arrowx - 1;
		}
		else if(direction == 4 && (arrowx+1)<cave_size && wumpus == false){
			cout << "Shoot East" << endl;
			arrowx = arrowx + 1;
		}
		else{
			cout << "Arrow hit a wall!" << endl;
			break;
		}
		if(arrowy == wumpusy && arrowx == wumpusx){
			cout << "You killed the Wumpus" << endl;
			cave[wumpusy][wumpusx]->delete_event();
			cave[wumpusy][wumpusx]->set_event_num(0);
			wumpus = true;
			return;
		}
	}
	cout << "Arrow didn't hit anything!" << endl;
	arrows = arrows - 1;
	cout << "Arrows left: " << arrows << endl;

	if(wumpus == false){
		bool wumpus_set;
		cave[wumpusy][wumpusx]->delete_event();
		cave[wumpusy][wumpusx]->set_event_num(0);
		while(wumpus_set == false){
			wumpusx = rand()%cave_size;
			wumpusy = rand()%cave_size;
			if(cave[wumpusy][wumpusx]->get_event_num() == 0){
				cave[wumpusy][wumpusx]->set_event(2);
				cave[wumpusy][wumpusx]->set_event_num(2);
				wumpus_set = true;
			}
		}
	}
}

//Run all the events
void Game::run_event(){
	if(cave[playery][playerx]->get_event_num() == 1){
		cout << "You are at the rope!" << endl;
		if(has_gold == true && wumpus == true){
			win = true;
			cout << "Winner" << endl;
		}
	}
	else if(cave[playery][playerx]->get_event_num() == 2){
		cout << "You've run into the wumpus!" << endl;
		is_alive = false;
		return;
	}
	else if(cave[playery][playerx]->get_event_num() == 3){
		cout << "You've found the gold!" << endl;
		has_gold = true;
		return;
	}
	else if(cave[playery][playerx]->get_event_num() == 4){
		cout << "You've fallen into a pit!" << endl;
		is_alive = false;
		return;
	}
	else if(cave[playery][playerx]->get_event_num() == 5){
		cave[playery][playerx]->set_player(false);
		cout << "You've been carried away by super bats!" << endl;
		int num1 = rand()%cave_size;
		int num2 = rand()%cave_size;
		playerx = num1;
		playery = num2;
		cave[playery][playerx]->set_player(true);
		return;
	}
}

//Checks if the user is alive
bool Game::check_is_alive(){
	if(arrows<=0){
		cout << "You've run out of arrows!" << endl;
		is_alive = false;
		return false;
	}
	if(cave[playery][playerx]->get_event_num() == 1){
		if(has_gold == true && wumpus == true){
			win = true;
			cout << "WINNER!" << endl;
			return false;
		}
	}
	else if(cave[playery][playerx]->get_event_num() == 2){
		cout << "You've ran into them wumpus!" << endl;
		is_alive = false;
		return false;
	}
	else if(cave[playery][playerx]->get_event_num() == 3){
		cout << "You've found the gold!" << endl;
		has_gold = true;
		return true;
	}
	else if(cave[playery][playerx]->get_event_num() == 4){
		cout << "You've fallen into a pit!" << endl;
		is_alive = false;
		return false;
	}
	return true;
}

//Resets the game with same conditions
void Game::game_reset(){
	cave[playery][playerx]->set_player(false);
	playerx = startx;
	playery = starty;
	cave[playery][playerx]->set_player(true);
	if(wumpus == false){
		cave[wumpusy][wumpusx]->delete_event();
		cave[wumpusy][wumpusx]->set_event_num(0);
	}
	wumpusx = startwx;
	wumpusy = startwy;
	cout << "Reset Wumpus y: " << wumpusy << endl;
	cout << "reset Wumpus x: " << wumpusx << endl;
	cave[wumpusy][wumpusx]->set_event(2);
	cave[wumpusy][wumpusx]->set_event_num(2);
	has_gold = false;
	is_alive = true;
	win = false;
	wumpus = false;
}

//Checks if user is alive
bool Game::get_is_alive(){
	return is_alive;
}

//Get win condition
bool Game::get_win(){
	return win;
}
