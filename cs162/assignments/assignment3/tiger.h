/*****************
 *Program: tiger.h
 *Author: Jackson E. Rollins
 *Date: 5/10/2020
 *Description: Header file for my tiger class
 * *************/
#ifndef TIGER_H
#define TIGER_H

#include <iostream>
#include <string>
#include "animal.h"

using namespace std;

//Tiger class
class Tiger : public Animal{
	public:
		Tiger();
		Tiger(string, int, int, int, int, int);
};

#endif
