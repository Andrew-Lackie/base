#ifndef _VECTORS_H
#define _VECTORS_H

#include "defines.h"
#include <stdlib.h>

// ToDo: Add a macro to initialize nested vectors

#define VECTOR_INIT(vec, capacity) vector vec; vector_init(&vec, capacity)
#define VECTOR_GET(vec, type, id) *(type*) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_TOTAL(vec) vector_total(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, item)
#define VECTOR_ADD(vec, item) vector_push_back(&vec, item)

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINED  -1
#define SUCCESS 0

typedef struct vec_list
{
    void **elements;
    i32 capacity;
    i32 total;
} vec_list;

//structure contains the function pointers
typedef struct vec vector;

struct vec
{
    vec_list vector_list;
    //function pointers
    i32 (*pf_vector_total)(vector *);
    i32 (*pf_vector_resize)(vector *, i32);
    i32 (*pf_vector_add)(vector *, void *);
    i32 (*pf_vector_set)(vector *, i32, void *);
    void *(*pf_vector_get)(vector *, i32);
    i32 (*pf_vector_delete)(vector *, i32);
    i32 (*pf_vector_free)(vector *);
};

i32 vector_total(vector *v);

i32 vector_resize(vector *v, i32 capacity);

i32 vector_push_back(vector *v, void *item);

i32 vector_set(vector *v, i32 index, void *item);

void *vector_get(vector *v, i32 index);

i32 vector_delete(vector *v, i32 index);

i32 vector_free(vector *v);

void vector_init(vector *v, size_t capacity);

#endif
