#include "philo.h"


// main.c is the entry point of the program. It initializes the simulation, creates philosopher threads, and manages the overall flow of the dining philosophers problem. The main function will parse command-line arguments, set up the shared table structure, create philosopher threads, and wait for them to finish before cleaning up resources.
// is a TLDR of the main.c file, which serves as the entry point for the dining philosophers simulation. It is responsible for initializing the simulation, creating philosopher threads, and managing the overall flow of the program. The main function will parse command-line arguments to set up the shared table structure, create philosopher threads, and wait for them to finish before cleaning up resources.
// ./philo num_philos time_to_die time_to_eat time_to_sleep [meals_required]

int main(int argc, char *argv[]) {
    // The main function will parse command-line arguments, set up the shared table structure, create philosopher threads, and wait for them to finish before cleaning up resources.
    
    t_table table;
    if (argc == 5 || argc == 6) {

        // 01
        // Correct number of arguments, proceed with initialization
        // Initialize the table structure with the provided arguments
        parse_input(argv, &table); // This function will parse the command-line arguments and initialize the table structure accordingly.

        // 02
        // Data initialization and thread creation logic will go here, but is not included in this snippet.
        // creatting the table and the philosophers will be done in the main function, but is not included in this snippet.
        data_init(&table); // This function will initialize the data structures for the philosophers and forks based on the number of philosophers specified in the table structure. It will allocate memory for the philosophers and forks, initialize their attributes, and set up any necessary synchronization primitives (e.g., mutexes for the forks).

        // 03
        // After initialization, we will start the simulation by creating philosopher threads and managing their execution.
        dinner_philosophers(&table); // This function will handle the main logic of the dining philosophers simulation, including thread creation and management.


        // 04 
        // After the simulation is complete, we will clean up resources, such as freeing memory and destroying mutexes.
        cleanup(&table); // This function will clean up resources, such as freeing memory and destroying mutexes, after the simulation is complete.



    }else {
        error_exit("Invalid number of arguments. Usage:\n" 
            GREEN" ./philo num_philos time_to_die time_to_eat time_to_sleep [meals_required]" RESET); 
        return 1;
    }
    
    return 0;
}

