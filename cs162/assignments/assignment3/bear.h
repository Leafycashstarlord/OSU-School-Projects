/*************
 *Program: bear.h
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Header file for the bear class
 * ***********/
#ifndef BEAR_H
#define BEAR_H

#include <iostream>
#include <string>
#include "animal.h"

using namespace std;

//Bear class
class Bear : public Animal{
	public:
		Bear();
		Bear(string, int, int, int, int, int);
};

#endif
