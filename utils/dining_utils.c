#include "philo.h"

/* Philosopher actions: eat, sleep, think. */
void eating(t_philo *philo) {
    safe_mutex_handler(&philo->first_fork->fork, LOCK);
    write_mutex(TAKEN_FIRST_FORK, philo, false);
    safe_mutex_handler(&philo->second_fork->fork, LOCK);
    write_mutex(TAKEN_SECOND_FORK, philo, false);

    set_long_value(&philo->table->table_mutex, &philo->last_meal_time, get_time_in_ms(MILLISECOND));
    philo->meals_counter++;
    write_mutex(EATING, philo, false);
    precision_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->num_meals_required >= 0 && philo->meals_counter == philo->table->num_meals_required) {
        set_bool_value(&philo->philo_mutex, &philo->full, true);
    }
    safe_mutex_handler(&philo->second_fork->fork, UNLOCK);
    safe_mutex_handler(&philo->first_fork->fork, UNLOCK);

}

void thinking(t_philo *philo, bool pre_simulation) {
  
    long time_to_eat;
    long time_to_sleep;
    long time_to_think;

    if(!pre_simulation) {
        write_mutex(THINKING, philo, false);
    }

    if(philo->table->num_philos % 2 == 0) 
        return;
    time_to_eat = philo->table->time_to_eat;
    time_to_sleep = philo->table->time_to_sleep;
    time_to_think = time_to_eat * 2 - time_to_sleep;
    if(time_to_think < 0) {
        time_to_think = 0;
    }

    precision_usleep(time_to_think * 0.42, philo->table);

    // write_mutex(THINKING, philo, DEBUG_MODE);
}

void sleeping(t_philo *philo) {
    write_mutex(SLEEPING, philo, false);
    precision_usleep(philo->table->time_to_sleep, philo->table);
}