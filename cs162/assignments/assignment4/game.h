/***********
 *Jackson E. Rollins
 *5/25/2020
 *Game header file
 * **********/
#ifndef GAME_H
#define GAME_H

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

using namespace std;

//Game class
class Game : Room{
	protected:
		vector<vector<Room*>>cave;
		int cave_size;
		int arrows = 3;
		bool has_gold = false;
		int startx;
		int starty;
		int playerx;
		int playery;
		int startwx;
		int startwy;
		int wumpusx;
		int wumpusy;
		int arrowx;
		int arrowy;
		bool wumpus = false;
		bool is_alive = true;
		bool win = false;
	public:
		Game(int size);
		~Game();
		void print_nearby_event();
		void print_board();
		void set_board();
		void print_player_board();
		void move_player(int);
		void shoot_arrow(int);
		void run_event();
		bool check_is_alive();
		void game_reset();
		bool get_is_alive();
		bool get_win();
};

#endif
