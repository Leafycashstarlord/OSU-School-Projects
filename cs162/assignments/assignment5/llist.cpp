/**************
 *Jackson E. Rollins
 *6/7/2020
 *Implementation file for the linked list class
 * ***********/
#include <iostream>
#include <string>
#include "node.h"
#include "llist.h"

using namespace std;

//Default constructor for the linked list class
Linked_List::Linked_List(){
	length = 0;
	head->val = 0;
	head->next = NULL;
}

//Custum Constructor for linked list class
Linked_List::Linked_List(int num){
	length = 1;
	head->val = num;
	head->next = NULL;
}

//Function that retrieves the length of the list
int Linked_List::get_length(){
	return length;
}

//Function that pritns the list
void Linked_List::print(){
	Node *temp = new Node;
	temp = head;

	cout << "List: " << endl;
	while(temp != NULL){
		cout << temp->val << " ";
		temp = temp->next;
	}
	cout << endl;
}

//Function the deletes the list
void Linked_List::clear(){
	delete head;
	head = NULL;
	length = 0;
}

//Function the inserts the given value at the end of the list
unsigned int Linked_List::push_back(int num){
	Node *temp1 = new Node;
	temp1->val = num;
	temp1->next = NULL;

	if(head = NULL){
		head = temp1;
	}else{
		Node *temp2 = new Node;
		temp2 = head;

		while(temp2 != NULL){
			temp2->next;
		}

		temp2 = temp1;
	}

	length++;
	return length;
}

//Function that inserts the given value to the front of the list
unsigned int Linked_List::push_front(int num){
	Node *temp = new Node;
	temp->val = num;
	temp->next = head;
	head = temp;
	cout << "Hell" << endl;
	length++;
	return length;
}

//Function that allows the user to insert a value anywhere they want int he list
unsigned int Linked_List::insert(int val, unsigned int index){
	Node *temp1 = new Node;
	Node *temp2 = new Node;
	Node *temp3 = new Node;

	temp1 = head;
	temp2 = head;
	for(int i = 0; i < index - 1; i++){
		temp1 = temp1->next;
	}
	temp3 = temp1->next;
	temp2->val = val;
	temp2->next = temp3;
	temp1->next = temp2;

	length++;
	return length;
}

//Function that sorts each of the smallest lists for the merge sort
Node* Linked_List::mergeList(Node *temp1, Node *temp2, int num){
	Node *result = new Node;

	result = NULL;
	if(temp1 == NULL){
		return temp2;
	}
	if(temp2 == NULL){
		return temp1;
	}
	if(num == 1){
		if(temp1->val < temp2->val){
			result = temp1;
			result->next = mergeList(temp1->next, temp2, num);
		}else{
			result = temp2;
			result->next = mergeList(temp1, temp2->next, num);
		}

		return result;
	}else if(num == 2){
		if(temp1->val > temp2->val){
			result = temp1;
			result->next = mergeList(temp1->next, temp2, num);
		}else{
			result = temp2;
			result->next = mergeList(temp1, temp2->next, num);
		}
	}
}

//Function that splits the list into smalle rlists for the merge sort
void Linked_List::split(Node *temp1, Node **temp2, Node **temp3){
	Node *t1 = new Node;
	Node *t2 = new Node;

	t1 = temp1;
	t2 = temp1->next;
	while(t2 != NULL){
		t2 = t2->next;
		if(t2 != NULL){
			t1 = t1->next;
			t2 = t2->next;
		}
	}
	*temp2 = temp1;
	*temp3 = t1->next;
	t1->next = NULL;
}

//Function that completes the merge sort of the list
void Linked_List::mergeSort(Node **head, int num){
	Node *temp1 = new Node;
	Node *temp2 = new Node;
	Node *temp3 = new Node;

	temp1 = *head;
	temp2 = NULL;
	temp3 = NULL;
	if(temp1 == NULL || temp1->next == NULL){
		return;
	}
	split(temp1, &temp2, &temp3);
	mergeSort(&temp2, num);
	mergeSort(&temp3, num);
	*head = mergeList(temp2, temp3, num);
}

//Function the sorts the list in ascending order
void Linked_List::sort_ascending(){
	mergeSort(&head, 1);
}

//Function that sorts the list in descending order
void Linked_List::sort_descending(){
	mergeSort(&head, 2);
}
