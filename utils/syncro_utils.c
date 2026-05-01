#include "philo.h"

/*
 * Philosophers sit around a table with forks between them.
 * To eat, each needs two forks (left and right).
 * Problem: if everyone grabs one fork, no one can eat (deadlock).
 * Also, some may never get a chance to eat (starvation).
 * Goal: make sure everyone can eat safely.
 * Solution: use mutexes/semaphores to control fork usage.
*/

void wait_all_thread_ready(t_table *table) {

    while (!get_bool_value(&table->table_mutex, &table->all_thread_ready)) {
        usleep(100);
    }

    while (!simulation_start(table)) {
        usleep(100);
    }
}
