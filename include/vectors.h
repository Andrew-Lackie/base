#ifndef _VECTORS_H
#define _VECTORS_H

#include "defines.h"
#include <stdlib.h>
#include <stdbool.h>

// ToDo: Add a macro to initialize nested vectors

#define VECTOR_INIT(vec, capacity) vector vec; vector_init(&vec, capacity)
#define VECTOR_GET(vec, type, id) *(type*) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_TOTAL(vec) vector_total(&vec)
#define VECTOR_CAPACITY(vec) vector_capacity(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, item)
#define VECTOR_ADD(vec, item) vector_push_back(&vec, item)

#define UNDEFINED  -1
#define SUCCESS 0

typedef struct element {
    void* data;
    bool is_set;
} v_element;

typedef struct vec_list {
    void **elements;
    size_t capacity;
    size_t total;
} vec_list;

//structure contains the function pointers
typedef struct vec vector;

struct vec {
    vec_list vector_list;
    //function pointers
    size_t (*pf_vector_total)(vector *);
    size_t (*pf_vector_capacity)(vector *);
    i32 (*pf_vector_resize)(vector *, size_t);
    i32 (*pf_vector_add)(vector *, void *);
    i32 (*pf_vector_set)(vector *, size_t, void *);
    void *(*pf_vector_get)(vector *, size_t);
    i32 (*pf_vector_delete)(vector *, size_t);
    i32 (*pf_vector_free)(vector *);
};

size_t vector_total(vector *v);

size_t vector_capacity(vector *v);

bool vector_is_set(vector *v, size_t index);

i32 vector_resize(vector *v, size_t capacity);

i32 vector_push_back(vector *v, void *item);

i32 vector_set(vector *v, size_t index, void *item);

void *vector_get(vector *v, size_t index);

i32 vector_delete(vector *v, size_t index);

i32 vector_free(vector *v);

void vector_init(vector *v, size_t capacity);

#endif
