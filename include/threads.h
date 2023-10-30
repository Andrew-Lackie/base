#ifndef _THREADS_H
#define _THREADS_H

#include "defines.h"
#include "cpu.h"
#include <math.h>
#include <pthread.h>

typedef struct thread_data {
    void *data;
    size_t total_threads;
    size_t thread_count;
    size_t task;
    size_t tasks_per_thread;
    size_t tasks_per_last_thread;
} thread_data;

i32 thread_manager(void* obj, void* (*f)(void*), const pthread_attr_t* attr, size_t total_tasks, size_t total_threads);

#endif
