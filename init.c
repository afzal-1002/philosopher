#include "philo.h"


void philo_init(t_table *table) ;
void data_init(t_table *table) ;
void assign_forks(t_philo *philo, t_fork *forks, int index);

/*
 * This function will initialize the data structures for the philosophers 
 * and forks based on the number of philosophers specified in the table structure. 
 * It will allocate memory for the philosophers and forks, initialize their attributes, 
 * and set up any necessary synchronization primitives (e.g., mutexes for the forks).
*/

void data_init(t_table *table) {

    int i;

    i = 0;
    table->simulation_start_time = 0;
    table->simulation_end_time = 0;
    table->all_thread_ready = false;
    table->philos = safe_malloc(sizeof(t_philo) * table->num_philos);
    table->philos = safe_malloc(sizeof(t_philo) * table->num_philos);
    table->forks = safe_malloc(sizeof(t_fork) * table->num_philos);
    safe_mutex_handler(&table->table_mutex, INIT);
    while (i < table->num_philos) {
        safe_mutex_handler(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
        i++;
    }

    philo_init(table);
 
}

void philo_init(t_table *table) {

    int i;
    t_philo *philo;

    i = 0;
    while (i < table->num_philos) {
        philo = table->philos+i;
        philo->ph_id = i + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->last_meal_time = 0;
        philo->table = table;
        assign_forks(philo, table->forks, i);


        i++;
    }
}

void assign_forks(t_philo *philo, t_fork *forks, int index) {

    int num_philos = philo->table->num_philos;

    if(philo->ph_id % 2 == 0) {
        philo->first_fork = &forks[index];
        philo->second_fork = &forks[(index + 1) % num_philos];
    } else {
        philo->first_fork = &forks[(index + 1) % num_philos];
        philo->second_fork = &forks[index];
    }
    
}