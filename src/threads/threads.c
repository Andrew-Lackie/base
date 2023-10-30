#include <threads.h>

i32 thread_manager(void* obj, void* (*f)(void*), const pthread_attr_t* attr, size_t total_tasks, size_t total_threads) {

    cpu_info cpu = core_count();

    total_threads = cpu.cores;

    if (total_tasks < 1000) {
        LOG_WARN("Multithreading is inefficient for smaller computations.");
    }

    if (total_threads == 0) {
        LOG_WARN("Custom params set to true but thread_count set to 0; reverting to default params.");
        total_threads = cpu.cores;
    }
    else {

        if (total_threads > total_tasks) {
            LOG_WARN("Specified thread count is larger than total tasks; reverting to default params.");
            total_threads = total_tasks;
        }

        if (total_threads > cpu.cores) {
            LOG_INFO("Creating more threads than cpu cores; this may be inefficient.");
        }
        else if (total_threads < cpu.cores) {
            LOG_INFO("Creating less threads than cores; this may be inefficient.");
        }
    }

    size_t tasks_per_thread =  floor((f32) total_tasks / (f32) total_threads);
    size_t tasks_per_last_thread = total_tasks % tasks_per_thread + tasks_per_thread;

    if (total_tasks < total_threads) {
        total_threads = total_tasks;
    }

    thread_data arg;

    arg.data = obj;
    arg.tasks_per_thread = tasks_per_thread;
    arg.tasks_per_last_thread = tasks_per_last_thread;
    arg.total_threads = total_threads - 1;
    arg.thread_count = 0;
    arg.task = 0;

    // declaring threads

    pthread_t threads[total_threads];

    i32 status;

    // Creating four threads, each evaluating its own part
    for (size_t i = 0; i < total_threads; i++) {
        status = pthread_create(&threads[i], attr, f, (void*)&arg);
    }

    // joining and waiting for all threads to complete
    for (size_t i = 0; i < total_threads; i++)
        pthread_join(threads[i], NULL);

    return status;
}
