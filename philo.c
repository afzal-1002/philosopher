#include "philo.h"

/* Entry point: parse input, initialize data, run simulation, cleanup. */
int main(int argc, char **argv) {
    t_table table;
    if (argc == 5 || argc == 6) {
        parse_input(argv, &table);
        data_init(&table);
        dinner_philosophers(&table);
        cleanup(&table);
    }else {
        error_exit("Invalid number of arguments. Usage:\n" 
            GREEN" ./philo num_philos time_to_die time_to_eat time_to_sleep [meals_required]" RESET); 
        return 1;
    }
    
    return 0;
}

