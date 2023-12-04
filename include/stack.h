#ifndef _LL_STACK_H
#define _LL_STACK_H

#include <ll.h>
#include <vectors.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum IMPL_TYPE {
	LL,
	VECTOR
} IMPL_TYPE;

typedef struct  Stack {
	IMPL_TYPE impl_type;
	union {
		List* ll;
		Vector vec;
	};
} Stack;

/*
 * Stack
 */

Stack* stack_init(IMPL_TYPE type, size_t capacity);

i32 stack_push(Stack* stack, void* data);

i32 stack_pop(Stack* stack);

void* stack_show(Stack* stack);

bool stack_is_empty(Stack* stack);

size_t stack_total(Stack* stack);

i32 stack_remove(Stack* stack);

#endif
