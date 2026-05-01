#include "philo.h"

/* Synchronization helpers for start barrier and thread counters. */
void wait_all_thread_ready(t_table *table) {

    while (!get_bool_value(&table->table_mutex, &table->all_thread_ready)) {
        usleep(100);
    }

    while (!simulation_start(table)) {
        usleep(100);
    }
}


void increment_long(t_mutex *mutex, long *validate_input) {
    safe_mutex_handler(mutex, LOCK);
    (*validate_input)++;
    safe_mutex_handler(mutex, UNLOCK);
}


/* Return true when all philosopher threads have started running. */
bool all_thread_running(t_mutex *mutex, long *thread_running_count, long num_philos) {
    bool all_running;

    all_running = false;
    safe_mutex_handler(mutex, LOCK);
    all_running = (*thread_running_count == num_philos);
    safe_mutex_handler(mutex, UNLOCK);

    return all_running;
}
