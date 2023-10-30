#ifndef _MEMORY_H
#define _MEMORY_H

#include "defines.h"

/**
 * Tags to track memory allocation
 **/

typedef enum memory_tag {
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_VECTOR,
    MEMORY_TAG_MATRIX,
    MEMORY_TAG_STRING,
    MEMORY_TAG_LINEAR_ALLOCATOR,
    MEMORY_TAG_THREADS,
    MEMORY_TAG_HASHTABLE,
    MEMORY_TAG_MAX_TAGS
} memory_tag;

/**
 * Totally memory struct
 **/

typedef struct {
    size_t total_alloc_size;
} memory_system_configuration;

/**
 * Memory system initalizer
 **/

void initialize_memory();

/**
 * Allocate memory
 **/

void* m_allocate(size_t size, memory_tag tag);

void* m_reallocate(void*, size_t size, memory_tag tag);

void* m_allocate_aligned(size_t size, memory_tag tag, size_t alignment);

/**
 * Free allocated memory
 **/

void m_free(void* block, size_t size, memory_tag tag);

/**
 * Zeroes out the provided block of memory
 **/

void* m_zero_memory(void* block, size_t size);

/**
 * Copies the source block to the destination block
 **/

void* m_copy_memory(void* dest, const void* source, size_t size);

/**
 * Initializes each component in the block to a value
 **/

void* m_set_memory(void* dest, i32 value, size_t size);

/**
 * Gets the memory usage string
 **/

char* get_memory_usage_str();

#endif
