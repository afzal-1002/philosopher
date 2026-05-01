#include "philo.h"


void write_mutex(t_philo_status status, t_philo *philo, bool debug);
void write_status_debug(t_philo_status status, t_philo *philo, long elasped_time);


/* Thread-safe status printing with timestamps. */
void write_mutex(t_philo_status status, t_philo *philo, bool debug) {

    long elasped_time;

    elasped_time = get_time_in_ms(MILLISECOND) - philo->table->simulation_start_time;

    if(philo == NULL) {
        error_exit("Philo pointer is NULL in write_mutex function.");
        return;
    }

    safe_mutex_handler(&philo->table->write_mutex, LOCK);

     if (debug) {
        write_status_debug(status, philo, elasped_time);
    }else {
        if((TAKEN_FIRST_FORK == status || TAKEN_SECOND_FORK == status) && !simulation_end(philo->table)) {
            printf(WHITE "%-6ld " RESET "%d has taken a fork\n", elasped_time, philo->ph_id);
        }else if (EATING == status && !simulation_end(philo->table)) {
            printf(WHITE "%-6ld " RESET "%d is eating\n", elasped_time, philo->ph_id);
        }else if (SLEEPING == status && !simulation_end(philo->table)) {
            printf(WHITE "%-6ld " RESET "%d is sleeping\n", elasped_time, philo->ph_id);
        }else if (THINKING == status && !simulation_end(philo->table)) {
            printf(WHITE "%-6ld " RESET "%d is thinking\n", elasped_time, philo->ph_id);
        }else if (DEAD == status ) {
            printf(RED "%-6ld " RESET "%d has died\n", elasped_time, philo->ph_id);
        }
    }

    safe_mutex_handler(&philo->table->write_mutex, UNLOCK);
}


void write_status_debug(t_philo_status status, t_philo *philo, long elasped_time) {
    if(TAKEN_FIRST_FORK == status && !simulation_end(philo->table)) {
        printf(WHITE "%-6ld " RESET "%d has taken the 1st fork 🍴\n"
            "\t\t\n%d [ ] %d\n" RESET, elasped_time, philo->ph_id,
            philo->ph_id, philo->first_fork->fork_id);
    }else if (TAKEN_SECOND_FORK == status && !simulation_end(philo->table)) {
        printf(WHITE "%-6ld " RESET "%d has taken the 2nd fork 🍴\n"
            "\t\t\n%d [ ] %d\n" RESET, elasped_time, philo->ph_id,
            philo->ph_id, philo->second_fork->fork_id);
    }else if (EATING == status && !simulation_end(philo->table)) {
        printf(WHITE "%-6ld " RESET "%d is eating 🍽️\n"
            "\t\t\n%d [ ✓ ] %ld\n" RESET, elasped_time, philo->ph_id,
            philo->ph_id, philo->meals_counter);
    }else if (SLEEPING == status && !simulation_end(philo->table)) {
        printf(WHITE "%-6ld " RESET "%d is sleeping 😴\n" RESET, elasped_time, philo->ph_id);
    }else if (THINKING == status && !simulation_end(philo->table)) {
        printf(WHITE "%-6ld " RESET "%d is thinking 🤔\n" RESET, elasped_time, philo->ph_id);
    }else if (DEAD == status && !simulation_end(philo->table)) {
        printf(RED "%-6ld " RESET "%d has died 💀\n" RESET, elasped_time, philo->ph_id);
    }

}