#include "philo.h"

/* Monitor thread: waits for startup, then checks philosopher death. */
void *monitor_dinner(void *data) {
    t_table *table = (t_table *)data;
    int i;

    while (!all_thread_running(&table->table_mutex, &table->thread_running_count, table->num_philos))
        ;
    while (!simulation_end(table)) {
        i = 0;
        while (i < table->num_philos && !simulation_end(table)) {
            if (philo_is_dead(table->philos + i)) {
                set_bool_value(&table->table_mutex, &table->simulation_should_end, true);
                write_mutex(DEAD, table->philos + i, DEBUG_MODE);
            }
            i++;
        }
    }

    return (NULL);

}

/* Return true when a philosopher exceeded time_to_die and is not full. */
bool philo_is_dead(t_philo *philo) {
    long elapsed_time;
    long time_to_die;

    if(get_bool_value(&philo->philo_mutex, &philo->full)) {
        return false;
    }

    elapsed_time = get_time_in_ms(MILLISECOND) - get_long_value(&philo->table->table_mutex, &philo->last_meal_time) ;
    time_to_die = philo->table->time_to_die;

    if(elapsed_time > time_to_die) {
        return true;
    }
    return false;
}