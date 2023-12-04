#ifndef _VECTORS_H
#define _VECTORS_H

#include "defines.h"
#include <stdlib.h>
#include <stdbool.h>

#define UNDEFINED  -1
#define SUCCESS 0

typedef struct v_element {
    void* data;
    bool is_set;
} v_element;

typedef struct vec_list {
    void **elements;
    size_t capacity;
    size_t total;
} vec_list;

//structure contains the function pointers
typedef struct vec Vector;

struct vec {
    vec_list vector_list;
    //function pointers
    size_t (*pf_vector_total)(Vector *);
    size_t (*pf_vector_capacity)(Vector *);
    bool (*pf_vector_is_set)(Vector *v, size_t index);
    i32 (*pf_vector_resize)(Vector *, size_t);
    i32 (*pf_vector_add)(Vector *, void *);
    i32 (*pf_vector_set)(Vector *, size_t, void *);
    i32 (*pf_vector_add_next)(Vector *v, void *item);
    void *(*pf_vector_get)(Vector *, size_t);
    i32 (*pf_vector_delete)(Vector *, size_t);
    i32 (*pf_vector_free)(Vector *);
};

size_t vector_total(Vector *v);

size_t vector_capacity(Vector *v);

bool vector_is_set(Vector *v, size_t index);

i32 vector_resize(Vector *v, size_t capacity);

i32 vector_push_back(Vector *v, void *item);

i32 vector_set(Vector *v, size_t index, void *item);

i32 vector_add_next(Vector *v, void *item);

void *vector_get(Vector *v, size_t index);

i32 vector_delete(Vector *v, size_t index);

i32 vector_free(Vector *v);

Vector *vector_init(size_t capacity);

#endif
