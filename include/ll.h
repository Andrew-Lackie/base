#ifndef _LL_H
#define _LL_H

#include <logger.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define LL_VOIDPTR(x) (void*)&x
#define LL_CAST(list, type, position) (type*)(list->position)->data

typedef struct Node Node;

struct Node {
	void *data;
	Node* next;
};

typedef struct List List;

struct List {
	size_t size;
	Node* head;
};

/*
 * Create list
 */

List* ll_init();

/*
 * Insert nodes
 */

Node* ll_insert_begin(List* list, void *data);

Node* ll_insert_end(List* list, void *data);

Node* ll_insert_index(List* list, void *data, int index);

/*
 * Remove nodes
 */

i32 ll_remove_begin(List* list);

i32 ll_remove_end(List* list);

i32 ll_remove_index(List* list, int index);

/*
 * Print nodes
 */

void ll_print(List* list, void *data, int index);

#endif
