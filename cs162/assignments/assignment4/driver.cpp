/*********
 *Jackson E. Rollins
 *5/25/2020
 *Driver file, runs the whole program
 * *********/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "event.h"
#include "room.h"
#include "bats.h"
#include "wumpus.h"
#include "gold.h"
#include "pit.h"
#include "empty.h"
#include "game.h"

using namespace std;

//Main function that runs everything
int main(int argc, char** argv){
	srand(time(NULL));
	int size = atoi(argv[1]);
	int stop = 1;
	int option = 100;
	char direction;
	int again = 1;

	Game* game = new Game(size);
	while(again == 1 || again == 2){
		if(again == 1){
			game->set_board();
		}
		int option = 1;
		while(option != 0 && game->get_is_alive() == true && game->get_win() == false){
			if(game->check_is_alive() == false){
				game->print_board();
				cout << endl;
				game->print_player_board();
				break;
			}
			game->print_nearby_event();
			game->print_board();
			cout << endl;
			game->print_player_board();
			cout << "Press 1 to move, 2 to shoot arrows, 0 to stop" << endl;
			cin >> option;
			if(option == 1){
				cout << "Press w to move north" << endl;
				cout << "Press s to move south" << endl;
				cout << "Press a to move west" << endl;
				cout << "Press d to move east" << endl;
				cin >> direction;
				if(direction == 'w'){
					game->move_player(1);
				}
				else if(direction == 's'){
					game->move_player(2);
				}
				else if(direction == 'a'){
					game->move_player(3);
				}
				else if(direction == 'd'){
					game->move_player(4);
				}
				else{
					cout << "Not an option." << endl;
				}
				game->run_event();
			}
			else if(option == 2){
				cout << "Press w to shoot North" << endl;
				cout << "Press s to shoot South" << endl;
				cout << "Press a to shoot west" << endl;
				cout << "Press d to shoot east" << endl;
				cin>>direction;
				if(direction == 'w'){
					game->shoot_arrow(1);
				}
				else if(direction == 's'){
					game->shoot_arrow(2);
				}
				else if(direction == 'a'){
					game->shoot_arrow(3);
				}
				else if(direction == 'd'){
					game->shoot_arrow(4);
				}
				else{
					cout << "Not an option" << endl;
				}
			}

			cout << endl;
			cout << endl;
			cout << endl;
		}
		cout << "Play Again? 1 for New config, 2 for same config, 3 to stop" << endl;
		again;
		if(again == 1){
			delete game;
			Game* game = new Game(size);
		}
		else if(again == 2){
			game->game_reset();
		}
		else{
			delete game;
		}
	}
}
