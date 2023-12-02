#ifndef _LL_H
#define _LL_H

#include "defines.h"
#include <stdlib.h>

#define LL_VOIDPTR(x) (void*)&x
#define LL_CAST(list, type, position) (type*)(list->position)->data

typedef struct Node Node;

struct Node {
	void* data;
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
 * list total
 */

size_t ll_total(List* list);

/*
 * Insert nodes
 */

Node* ll_insert_begin(List* list, void *data);

Node* ll_insert_end(List* list, void *data);

Node* ll_insert_index(List* list, void *data, size_t index);

/*
 * Get Nodes
 */

Node* ll_get_begin(List* list);

Node* ll_get_end(List* list);

Node* ll_get_index(List* list, size_t index);

/*
 * Remove nodes
 */

i32 ll_remove_begin(List* list);

i32 ll_remove_end(List* list);

i32 ll_remove_index(List* list, size_t index);

/*
 * Remove list
 */

i32 ll_remove_list(List* list);

/*
 * Print nodes
 */

void ll_print(List* list, void *data, size_t index);

#endif
