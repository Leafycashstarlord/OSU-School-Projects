/**************
 *Jackson E. Rollins
 *6/7/2020
 * Header file for the linked list class
 * *************/
#ifndef LLIST_H
#define LLIST_H

#include <iostream>
#include <string>
#include "node.h"

using namespace std;

//Linked List class
class Linked_List{
	private:
		unsigned int length;
		Node *head;
	public:
		Linked_List();
		Linked_List(int);
		int get_length();
		void print();
		void clear();
		unsigned int push_back(int);
		unsigned int push_front(int);
		unsigned int insert(int val, unsigned int index);
		void sort_ascending();
		void sort_descending();
		void mergeSort(Node**, int);
		void split(Node*, Node**, Node**);
		Node *mergeList(Node*, Node*, int);
		
};

#endif
