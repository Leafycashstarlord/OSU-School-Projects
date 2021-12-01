/***********
 *Jackson E. Rollins
 *6/7/2020
 *Header file for my node class
 * **********/
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

//Node class
class Node{
	public:
		int val;
		Node *next;
		Node();
};

#endif
