#include "philo.h"


/*
    *./philo 5 800 200 200 [5]
    *  utils.c contains utility functions for the dining philosophers simulation.
    *  It includes error handling and input parsing to keep the code modular.
    *  The print_error function displays error messages in a consistent format.
    *  The parse_input function validates and parses command-line arguments.
    *  Program usage:
    *      ./philo num_philos time_to_die time_to_eat time_to_sleep [meals_required]
    *  The main function checks the number of arguments before calling parse_input.
    *  The parse_input function converts arguments from strings to numerical values
    *  and initializes the shared table structure.
    * 
    * 01) if no meal then return 0, if meal then return 1
    * 02) if meal then check if meal is enough, if not then return 0, if enough then return 1
    * 03) if only one philosopher then return 0, as he will never eat
    * 04) if philosopher is full then return 1, as he will not eat anymore
    * 05) if philosopher is not full then return 0, as he will eat until he is full
    * 06) Create a thread for each philosopher and start the simulation.
    * 07) Wait for all philosopher threads to finish before exiting the program.
    * 08) Clean up resources, such as freeing memory and destroying mutexes, after the simulation is complete.
    * 
    * Synchronize the beginning of the simulation pthread_create->philo 
    * sart running -> simulation start time is set -> all philosophers start their routine at the same time.
    * every philosopher will check the simulation start time before starting their routine, and if it is not set, they will wait until it is set.
    * This way, we can ensure that all philosophers start their routine at the same time, 
    * and we can accurately measure the time to die, time to eat, and time to sleep for each
*/

void dinner_philosophers(t_table *table);
void cleanup(t_table *table);
void *dinner_simulation(void *data);

void dinner_philosophers(t_table *table) {
    // This function will handle the main logic of the dining philosophers simulation, including thread creation and management.


    int i = 0;

    if(table->num_philos == 0){
        error_exit("There must be at least one philosopher to start the simulation.");
        return;
    }else if(table->num_philos == 1) {
        printf("Philosopher 1 has taken the left fork.\n");
        usleep(table->time_to_die);
        printf("Philosopher 1 has died.\n");
        return;
    }else {

        while (i < table->num_philos) {
            safe_thread_handler(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
            i++;
        }
    
        // Create a thread for each philosopher and start the simulation.
        // Wait for all philosopher threads to finish before exiting the program.
        // Clean up resources, such as freeing memory and destroying mutexes, after the simulation is complete.
    }

    // Now all philosopher threads have been created and are running their routine. We will wait for them to finish and then clean up resources.
    i = 0;
    while (i < table->num_philos) {
        safe_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }

}

void *dinner_simulation(void *data) {
    // This function will contain the routine for each philosopher, including thinking, eating, and sleeping.
    // It will also handle the logic for checking if a philosopher has died or is full.

    t_philo *philo = (t_philo *)data;

    wait_all_thread_ready(philo->table); // This function will ensure that all philosopher threads start their routine at the same time by waiting until the simulation start time is set.

    // Philosopher's routine will be implemented here, but is not included in this snippet.
    return NULL;
}