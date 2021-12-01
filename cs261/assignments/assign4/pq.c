/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Jackson E. Rollins
 * Email: rollijac@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
  struct dynarray* arr;
};

struct node{
  void* val;
  int prio;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  pq->arr = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->arr);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if(dynarray_size(pq->arr) == 0){
    return 1;
  }else{
    return 0;
  }
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  struct node* parent;
  struct node* child;
  struct node* node = malloc(sizeof(struct node));
  node->val = value;
  node->prio = priority;

  dynarray_insert(pq->arr, node);
  int index = dynarray_size(pq->arr) - 1;
  int prioIndex = (index-1)/2;

  while(index > 0){
    parent = dynarray_get(pq->arr, prioIndex);
    child = dynarray_get(pq->arr, index);

    if((parent->prio) > (node->prio)){
      struct node* temp = dynarray_get(pq->arr, index);
      dynarray_set(pq->arr, index, parent);
      dynarray_set(pq->arr, prioIndex, temp);
    }else{
      break;
    }
    index = prioIndex;
    prioIndex = (index-1)/2;
  }
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  struct node* node = dynarray_get(pq->arr, 0);
  return node->val;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct node* node = dynarray_get(pq->arr, 0);
  return node->prio;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  void* returnVal;
  struct node* childL;
  struct node* childR;
  struct node* current;
  struct node* nodeL = dynarray_get(pq->arr, dynarray_size(pq->arr)-1);
  struct node* nodeR = dynarray_get(pq->arr, 0);
  dynarray_set(pq->arr, 0, nodeL);
  dynarray_remove(pq->arr, dynarray_size(pq->arr)-1);
  int index = 0;
  int left = ((index*2)+1);
  int right = ((index*2)+2);
  int size = dynarray_size(pq->arr);
  while((size > left) || (size > right)){
    current = dynarray_get(pq->arr, index);
    childL = dynarray_get(pq->arr, left);
    if(size > right){
      childR = dynarray_get(pq->arr, right);
    }else{
      childR = NULL;
    }
    if(((current->prio) > (childL->prio)) || ((childR != NULL) &&((current->prio) > (childR->prio)))){
      if((childR == NULL) || (childR->prio) >= (childL->prio)){
        struct node* temp = current;
        dynarray_set(pq->arr, index, childL);
        dynarray_set(pq->arr, (index*2)+1, temp);
        index = (index*2)+1;
      }else if(childR != NULL){
        struct node* temp = current;
        dynarray_set(pq->arr, index, childR);
        dynarray_set(pq->arr, (index*2)+2, temp);
        index = (index*2)+2;
      }
    }else{
      index = size;
    }
    left = ((index*2)+1);
    right = ((index*2)+2);
  }
  returnVal = nodeR->val;
  free(nodeR);
  return returnVal;
}
