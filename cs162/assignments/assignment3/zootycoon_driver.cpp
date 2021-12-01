/******************
 * Program: zootycoon_driver.cpp
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Driver file for the program with my main function
 * ***************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "animal.h"
#include "tiger.h"
#include "sealion.h"
#include "bear.h"
#include "zoo.h"
#include "get_int.h"

using namespace std;

//Main function that runs the entire program
int main(){
	srand(time(NULL));
	Zoo zoo;
	do{
		zoo.play_game();
		int number = get_int("Do you want to quit? 1 for yes, 2 for no: ", 1, 2);
		if(number == 1){
			zoo.set_money(0);
		}
	}while(zoo.get_money() > 0);
	cout << "You ran out of money, and the zoo closed!" << endl;
	cout << "Thanks For Playing!";

	return 0;
}
