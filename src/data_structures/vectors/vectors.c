#include <vectors.h>
#include <logger.h>
#include <memory.h>
#include <string.h>

static void *vector_create_element(void* data)
{
    v_element *item = m_allocate(sizeof(v_element), MEMORY_TAG_VECTOR);

    item->data = data;
    item->is_set = false;

    return item;
}

size_t vector_total(Vector *v)
{
    return v->vector_list.total;
}

size_t vector_capacity(Vector *v)
{
    if (v == NULL) {
        return 0;
    }
    if (v->vector_list.elements == NULL) {
        return 0;
    }
    return v->vector_list.capacity;
}

bool vector_is_set(Vector *v, size_t index)
{
    bool is_set;

    if(v) {
        if (v->vector_list.elements[index] != NULL) {
            v_element *item = (v_element*) v->vector_list.elements[index];
            is_set = item->is_set;
        }
        else {
            is_set = false;
        }
    }
    else {
        LOG_WARN("vector_is_set: vector is NULL; element at index %d undefined", index);
        is_set = false;
    }
    return is_set;
}

i32 vector_resize(Vector *v, size_t capacity)
{
    i32 status = UNDEFINED;
    void **elements;

    if (v) {
        capacity = capacity == 0 ? 1 : capacity;
        if (capacity > vector_capacity(v)) {
            if (v->vector_list.elements == NULL) {
                v->vector_list.elements = m_allocate(sizeof(void *) * capacity, MEMORY_TAG_VECTOR);
            }
            else {
                elements = m_reallocate(v->vector_list.elements, sizeof(void *) * capacity, MEMORY_TAG_VECTOR);
                v->vector_list.elements = elements;
            }
            v->vector_list.capacity = capacity;
            status = SUCCESS;
        }
        else if (capacity < vector_capacity(v)) {
            elements = m_allocate(sizeof(void *) * capacity, MEMORY_TAG_VECTOR);
            memcpy(elements, v->vector_list.elements, sizeof(void*) * vector_total(v));
            v->vector_list.elements = elements;
            v->vector_list.capacity = capacity;
            status = SUCCESS;
        }
    }
    else
    {
	      LOG_ERROR("vector_resize: vector undefined, returning UNDEFINED.");
    }
    return status;
}

i32 vector_push_back(Vector *v, void *data)
{
    v_element *item = vector_create_element(data);
    item->is_set = true;

    i32 status = UNDEFINED;
    if (v) {
        if (v->vector_list.capacity == v->vector_list.total) {
            status = vector_resize(v, v->vector_list.capacity * 2);
            if(status != UNDEFINED) {
                v->vector_list.elements[v->vector_list.total++] = (void*) item;
            }
        }
        else {
            v->vector_list.elements[v->vector_list.total++] = (void*) item;
            status = SUCCESS;
        }
    }
    else {
	      LOG_ERROR("vector_push_back: vector undefined, returning UNDEFINED.");
    }
    return status;
}

i32 vector_set(Vector *v, size_t index, void* data)
{
    v_element *item;

    i32 status = UNDEFINED;
    if(v) {
        if (index < v->vector_list.capacity) {
            item = v->vector_list.elements[index] == NULL ? vector_create_element(data) : (v_element*) v->vector_list.elements[index];
            if (!vector_is_set(v, index)) {
                item->is_set = true;
                v->vector_list.total++;
            }
            item->data = data;
            v->vector_list.elements[index] = (void*) item;
            status = SUCCESS;
        }
        else {
	          LOG_ERROR("vector_set: vector undefined at index %lu.", index);
        }
    }
    else {
	      LOG_ERROR("vector_set: vector undefined, returning UNDEFINED.");
    }
    return status;
}

i32 vector_add_next(Vector *v, void* data)
{
    i32 status = UNDEFINED;

    if (v) {
        size_t v_total = vector_total(v);
        size_t v_capacity = vector_capacity(v);

        if (v_total < v_capacity) {
            return vector_set(v, v_total, data);
        }
        else {
            return vector_push_back(v, data);
        }
    }
    else {
        LOG_ERROR("vector_set: vector undefined at index %lu.");
    }

    return status;
}

void *vector_get(Vector *v, size_t index)
{
    v_element* item;
    void* data = NULL;

    if (v) {
        if (index < vector_total(v)) {
            item = (v_element*) v->vector_list.elements[index];
            if (item == NULL) {
                LOG_WARN("vector_get: the element at index %d is NULL.", index);
                return NULL;
            }
            data = item->data;
        }
        else {
            LOG_WARN("vector_get: the vector at index %d is undefined.", index);
        }
    }
    else {
        LOG_WARN("vector_get: vector is NULL; element at index %d is undefined.", index);
    }
    return data;
}

i32 vector_delete(Vector *v, size_t index)
{
    i32 status = UNDEFINED;
    size_t i = 0;

    if (v) {
        if (index >= v->vector_list.capacity)
            return status;
        v->vector_list.elements[index] = NULL;
        for (i = index; (i < v->vector_list.total - 1); i++) {
            v->vector_list.elements[i] = v->vector_list.elements[i + 1];
            v->vector_list.elements[i + 1] = NULL;
        }
        v->vector_list.total--;
        if ((v->vector_list.total > 0) && ((v->vector_list.total) == (v->vector_list.capacity / 4))) {
            vector_resize(v, v->vector_list.capacity / 2);
        }
        status = SUCCESS;
    }
    else {
	      LOG_ERROR("vector_delete: vector undefined, returning UNDEFINED.");
    }
    return status;
}

i32 vector_free(Vector *v)
{
    i32  status = UNDEFINED;
    if (v) {
        m_free(v->vector_list.elements, v->vector_list.capacity, MEMORY_TAG_VECTOR);
        m_free(v, sizeof(Vector), MEMORY_TAG_VECTOR);
        status = SUCCESS;
    }
    else {
	      LOG_ERROR("vector_free: vector undefined, returning UNDEFINED.");
    }
    return status;
}

Vector *vector_init(size_t capacity)
{
    Vector *v = m_allocate(sizeof(Vector), MEMORY_TAG_VECTOR);

    // init function pointers
    v->pf_vector_total = vector_total;
    v->pf_vector_capacity = vector_capacity;
    v->pf_vector_is_set = vector_is_set;
    v->pf_vector_resize = vector_resize;
    v->pf_vector_add = vector_push_back;
    v->pf_vector_set = vector_set;
    v->pf_vector_add_next = vector_add_next;
    v->pf_vector_get = vector_get;
    v->pf_vector_free = vector_free;
    v->pf_vector_delete = vector_delete;

    // initialize the capacity and allocate the memory
    v->vector_list.capacity = capacity;
    v->vector_list.total = 0;
    v->vector_list.elements = capacity == 0 ? NULL : m_allocate(sizeof(void *) * v->vector_list.capacity, MEMORY_TAG_VECTOR);

    return v;
}
