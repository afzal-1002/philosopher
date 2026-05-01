#include "philo.h"


void wait_all_thread_ready(t_table *table) {


    while (!get_bool_value(&table->table_mutex, &table->all_thread_ready)) {
        usleep(100); // Sleep for a short time to avoid busy waiting
    }

    while (!simulation_start(table)) {
        usleep(100); // Sleep for a short time to avoid busy waiting
    }
}
