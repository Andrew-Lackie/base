#ifndef _LL_STACK_H
#define _LL_STACK_H

#include "ll.h"

extern struct Node *front;
extern struct Node *rear;

Node* enqueue(Node** node, void* value);

void dequeue(Node** node);

#endif
