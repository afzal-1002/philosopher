#include "philo.h"

void set_long_value(t_mutex *mutex, long *var, long value);

/*
     *eat() will handle the logic for a philosopher to eat, including picking up forks, updating meal counts, and checking if the philosopher is full.
     * It will also handle the logic for checking if a philosopher has died while trying to eat, and will update the philosopher's status accordingly.
     * The function will use mutexes to ensure that philosophers can safely pick up and put down forks without causing race conditions or deadlocks.
     * The eat function will also update the philosopher's last meal time and check if they have reached the required number of meals to be considered full.
     * If a philosopher dies while trying to eat, the function will set the simulation end flag to true and print a message indicating that the philosopher has died.
     * The eat function will also handle the logic for putting down forks after eating, ensuring that other philosophers can access the forks when they are done eating.
     * The function will also check if the simulation has ended before allowing the philosopher to eat, to prevent any actions from being taken after the simulation has ended.
     * Overall, the eat function will be a critical part of the dining philosophers simulation, as it will manage the core
*/


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

void thinking(t_philo *philo) {
    write_mutex(THINKING, philo, false);
}

void sleeping(t_philo *philo) {
    write_mutex(SLEEPING, philo, false);
    precision_usleep(philo->table->time_to_sleep, philo->table);
}