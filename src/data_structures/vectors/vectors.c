#include <vectors.h>
#include <logger.h>
#include <memory.h>

size_t vector_total(vector *v)
{
    return v->vector_list.total;
}

size_t vector_capacity(vector *v)
{
    return v->vector_list.capacity;;
}

i32 vector_resize(vector *v, size_t capacity)
{
    i32 status = UNDEFINED;
    if (v) {
        capacity = capacity == 0 ? 1 : capacity;
        void **elements = m_reallocate(v->vector_list.elements, sizeof(void *) * capacity, MEMORY_TAG_VECTOR);
        v->vector_list.elements = elements;
        v->vector_list.capacity = capacity;
        status = SUCCESS;
    }
    else
    {
	      LOG_ERROR("Vector undefined, returning -1.");
    }
    return status;
}

i32 vector_push_back(vector *v, void *item)
{

    i32 status = UNDEFINED;
    if (v) {
        if (v->vector_list.capacity == v->vector_list.total) {
            status = vector_resize(v, v->vector_list.capacity * 2);
            if(status != UNDEFINED) {
                v->vector_list.elements[v->vector_list.total++] = item;
            }
        }
        else {
            v->vector_list.elements[v->vector_list.total++] = item;
            status = SUCCESS;
        }
    }
    else {
	      LOG_ERROR("Vector undefined, returning -1.");
    }
    return status;
}

i32 vector_set(vector *v, size_t index, void* item)
{
    i32 status = UNDEFINED;
    if(v) {
        if (index < v->vector_list.capacity) {
            v->vector_list.elements[index] = item;
            v->vector_list.total++;
            status = SUCCESS;
        }
        else {
	          LOG_ERROR("Vector undefined at index %lu.", index);
        }
    }
    else {
	      LOG_ERROR("Vector undefined, returning -1.");
    }
    return status;
}

i32 vector_unset(vector *v, size_t index)
{
    i32 status = UNDEFINED;
    if(v) {
        if (index < v->vector_list.total) {
            v->vector_list.elements[index] = NULL;
            v->vector_list.total--;
            status = SUCCESS;
        }
    }
    else {
	      LOG_ERROR("Vector undefined, returning -1.");
    }
    return status;
}

void *vector_get(vector *v, size_t index)
{
    void *read_data = NULL;
    if(v) {
        if (index < vector_total(v)) {
            read_data = v->vector_list.elements[index];
        }
        else {
            LOG_WARN("The vector at index %d is undefined.", index);
            exit(1);
        }
    }
    else {
        LOG_WARN("Vector is NULL; returing NULL.");
    }
    return read_data;
}

i32 vector_delete(vector *v, size_t index)
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
	      LOG_ERROR("Vector undefined, returning -1.");
    }
    return status;
}

i32 vector_free(vector *v)
{
    i32  status = UNDEFINED;
    if (v) {
        m_free(v->vector_list.elements, v->vector_list.capacity, MEMORY_TAG_VECTOR);
        v->vector_list.elements = NULL;
        status = SUCCESS;
    }
    else {
	      LOG_ERROR("Vector undefined, returning -1.");
    }
    return status;
}

void vector_init(vector *v, size_t capacity)
{
    // init function pointers
    v->pf_vector_total = vector_total;
    v->pf_vector_resize = vector_resize;
    v->pf_vector_add = vector_push_back;
    v->pf_vector_set = vector_set;
    v->pf_vector_get = vector_get;
    v->pf_vector_free = vector_free;
    v->pf_vector_delete = vector_delete;
    // initialize the capacity and allocate the memory
    v->vector_list.capacity = capacity;
    v->vector_list.total = 0;
    v->vector_list.elements = capacity == 0 ? NULL : m_allocate(sizeof(void *) * v->vector_list.capacity, MEMORY_TAG_VECTOR);
}
