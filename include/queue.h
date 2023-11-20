#ifndef _LL_QUEUE_H
#define _LL_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <logger.h>
#include <memory.h>

#define Q_VOIDPTR(x) (void*)&x
#define Q_CAST(q, type, position) *(type*)(q->position)->data

typedef struct Node Node;

struct Node {
	void *data;
	Node* next;
};

typedef struct Queue Queue;

struct Queue {
	Node *front, *end;
	size_t size;
};

Queue* create_queue();

Node* enqueue(Queue *q, void *value);

void dequeue(Queue *q);

#endif
