#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

void initpQueue(pQueue **pqueue){
	(*pqueue) = (pQueue*)malloc(sizeof(pQueue));
	(*pqueue)->first = NULL;
	(*pqueue)->size = 0;
	return;
}
 
void addpQueue(pQueue **queue, TYPE val, unsigned int priority){
	if ((*queue)->size == Max_Size){
		printf("\nQueue is FULL\n");
		return;
	}
	pQueueNode *aux = (pQueueNode *)malloc(sizeof(pQueueNode));
	aux->priority = priority;
	aux->val = val;
	if ((*queue)->size == 0 || (*queue)->first == NULL){
		aux->Next = NULL;
		(*queue)->first = aux;
		(*queue)->size = 1;
		return;
	}
	else{
		if (priority <= (*queue)->first->priority){
			aux->Next = (*queue)->first;
			(*queue)->first = aux;
			((*queue)->size)++;
		}
		else{
			pQueueNode *iterator = (*queue)->first;
			while (iterator->Next != NULL){
				if (priority <= iterator->Next->priority){
					aux->Next = iterator->Next;
					iterator->Next = aux;
					(*queue)->size++;
					return;
				}
				iterator = iterator->Next;
			}
			if (iterator->Next == NULL){
				aux->Next = NULL;
				iterator->Next = aux;
				(*queue)->size++;
				return;
			}
		}
	}

}

TYPE getQueue(pQueue **queue){
	TYPE returnVal;
	if ((*queue)->size > 0){
		returnVal = (*queue)->first->val;
		(*queue)->first = (*queue)->first->Next;
		(*queue)->size--;
	}
	else{
		printf("\nQueue is empty\n");
	}
	return returnVal;
}