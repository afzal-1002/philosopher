#include "philo.h"

/* Free allocated resources and destroy all mutexes. */
void cleanup(t_table *table) {
    int i;

    if (table == NULL)
        return;

    /* Destroy all fork mutexes */
    if (table->forks != NULL) {
        i = 0;
        while (i < table->num_philos) {
            safe_mutex_handler(&table->forks[i].fork, DESTROY);
            i++;
        }
        free(table->forks);
        table->forks = NULL;
    }

    /* Destroy all philosopher mutexes and free memory */
    if (table->philos != NULL) {
        i = 0;
        while (i < table->num_philos) {
            safe_mutex_handler(&table->philos[i].philo_mutex, DESTROY);
            i++;
        }
        free(table->philos);
        table->philos = NULL;
    }

    /* Destroy table mutexes */
    safe_mutex_handler(&table->table_mutex, DESTROY);
    safe_mutex_handler(&table->write_mutex, DESTROY);
}
