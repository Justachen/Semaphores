// - Justin Chen -
// CSE330 Project3

#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"

// typedef struct TCB_t {
// 	int payload;
// 	struct TCB_t* next;
// 	struct TCB_t* prev;
// }TCB_t;


struct TCB_t* newItem(){
	//Creates struct for a new queue item
	TCB_t* item = malloc(sizeof(TCB_t));
	if(item) {
		item->prev = NULL;
		item->next = NULL;
	}
	return item;
}

void InitQueue(TCB_t** head)	{
	//creates new Queue struct
	*head = NULL;
}


void AddQueue(TCB_t** head, TCB_t* item) {
	TCB_t* temp = *head;

	if(temp == NULL)	{
		//Queue is empty
		*head = item;
		(*head)->prev = *head;
		(*head)->next = *head;
	}
	else if (temp->next == *head)
	{	//one element in queue

		(*head)->next = item;
		(*head)->prev = item;
		item->prev = *head;
		item->next = *head;

	}
	else
	{	//More than 1 element in queue
		while(temp->next != *head) {
			temp = temp->next;
		}
		item->next = temp->next;
		item->prev = temp;
		temp->next = item;
		(*head)->prev = item;
	}
}

struct TCB_t* DelQueue(struct TCB_t** head) {
	TCB_t* returner = *head;
	TCB_t* temp = *head;

	if (*head != NULL) {

	TCB_t* temp2 = (*head)->next;

	if (temp2 == *head) {
		*head = NULL;
		//return temp;
	}
	else
	{
		while (temp->next != *head) {
			temp = temp->next;
		}
		(*head) = temp2;
		temp->next = temp2;
		}
		//return (temp);
	}
	return (returner);
}

// void printq(TCB_t** head)	{
// 	TCB_t* temp = *head;
// 		if(temp != NULL) {
// 			while(temp->next != *head) {
// 				printf("%d\t", temp->payload);
// 				temp = temp->next;
// 			}
// 			printf("%d\n", temp->payload);
// 		}
// }

void RotateQ(TCB_t** head) {
	if(*head != NULL)
	*head = (*head)->next;
}
