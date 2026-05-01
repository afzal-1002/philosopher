#include "philo.h"


/*
 * Core dining simulation flow:
 * - Create philosopher threads.
 * - Create monitor thread.
 * - Synchronize start time.
 * - Join all threads before cleanup.
 */


/* Philosopher routine and simulation coordinator. */
void *dinner_simulation(void *data);
void dinner_start(t_table *table);


void dinner_start(t_table *table) {

    int i = 0;

    if(table->num_philos == 0){
        error_exit("There must be at least one philosopher to start the simulation.");
        return;
    }else if(table->num_philos == 1) {
        table->simulation_start_time = get_time_in_ms(MILLISECOND);
        printf("Philosopher 1 has taken the left fork.\n");
        usleep(table->time_to_die * 1000);
        printf("Philosopher 1 has died.\n");
        return;
    }else {

        while (i < table->num_philos) {
            safe_thread_handler(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
            i++;
        }
    
    }

    /* Monitor thread checks death/full conditions and ends simulation when needed. */
    safe_thread_handler(&table->monitor, monitor_dinner, table, CREATE);

    table->simulation_start_time = get_time_in_ms(MILLISECOND); // Set the simulation start time to the current time in milliseconds.
    set_bool_value(&table->table_mutex, &table->all_thread_ready, true); // Set the flag to indicate that all philosopher threads are ready to start their routine.

    // Now all philosopher threads have been created and are running their routine. We will wait for them to finish and then clean up resources.
    i = 0;
    while (i < table->num_philos) {
        safe_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }

    set_bool_value(&table->table_mutex, &table->simulation_should_end, true);
    safe_thread_handler(&table->monitor, NULL, NULL, JOIN);

}

void *dinner_simulation(void *data) {

    t_philo *philo = (t_philo *)data;
    long current_time;
    long time_since_last_meal;

    wait_all_thread_ready(philo->table);

    /* Initialize last meal timestamp. */
    set_long_value(&philo->table->table_mutex, &philo->last_meal_time, get_time_in_ms(MILLISECOND));

    /* Signal monitor that this philosopher thread is running. */
    increment_long(&philo->table->table_mutex, &philo->table->thread_running_count);


    /* Main simulation loop: eat -> sleep -> think */
    while (!simulation_end(philo->table)) {
        if (get_bool_value(&philo->philo_mutex, &philo->full))
            break;
        
        eating(philo);
        write_mutex(SLEEPING, philo, false);
        precision_usleep(philo->table->time_to_sleep, philo->table);
        thinking(philo, false);
     

        /* Check if philosopher has died */
        current_time = get_time_in_ms(MILLISECOND);
        time_since_last_meal = current_time - get_long_value(&philo->table->table_mutex, &philo->last_meal_time);
        
        if (time_since_last_meal > philo->table->time_to_die) {
            write_mutex(DEAD, philo, false);
            set_bool_value(&philo->table->table_mutex, &philo->table->simulation_should_end, true);
            break;
        }
    }

    return NULL;
}

/* Wrapper function for dinner_philosophers */
void dinner_philosophers(t_table *table) {
    dinner_start(table);
}

/* Optional one-philosopher routine retained for future use. */
void *lone_philosopher(void *data) {
    t_philo *philo = (t_philo *)data;

    wait_all_thread_ready(philo->table);
    set_long_value(&philo->table->table_mutex, &philo->last_meal_time, get_time_in_ms(MILLISECOND));
    increment_long(&philo->table->table_mutex, &philo->table->thread_running_count);
    write_mutex(TAKEN_FIRST_FORK, philo, DEBUG_MODE);

        while (!simulation_end(philo->table)) {
            usleep(200);
        }

    return NULL;
}