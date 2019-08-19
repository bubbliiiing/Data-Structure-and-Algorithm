#pragma once
#ifndef _PQUEUE_H
#define _PQUEUE_H
#include"huffman.h"
#define TYPE htNode*
#define Max_Size 256

typedef struct _pQueueNode{
	TYPE val;
	unsigned int priority;
	struct _pQueueNode* Next;
}pQueueNode;

typedef struct _pQueue{
	unsigned int size;
	pQueueNode *first;
}pQueue;

void initpQueue(pQueue **queue);
void addpQueue(pQueue **queue, TYPE val, unsigned int priority);
TYPE getQueue(pQueue **queue);
 
#endif