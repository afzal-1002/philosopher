#include "philo.h"


void error_exit(const char *message);
long get_time_in_ms(t_time_code time_code);
void precision_usleep(long duration_in_ms, t_table *table);

void error_exit(const char *message) {
    printf(RED "%s \n" RESET , message);
    exit(EXIT_FAILURE);
}

/*
 * time_code is a utility function that retrieves the current time in milliseconds.
 * gettimeofday() is a system call that retrieves the current time of day, 
 * expressed as the number of seconds and microseconds since the Unix epoch (January 1, 1970).
 * In the context of the dining philosophers problem, gettimeofday() can be used to measure the time 
 * taken for various actions, such as eating, sleeping, and thinking. 
 * By recording the start and end times of these actions, we can analyze
 *  the performance and behavior of the philosophers.
*/

long get_time_in_ms(t_time_code time_code) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    if(gettimeofday(&tv, NULL) == -1) {
        error_exit("Failed to get current time.");
    }

    if (time_code == SECOND)
        return (tv.tv_sec + tv.tv_usec / 1000000);
    else if (time_code == MILLISECOND)
        return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
    else if (time_code == MICROSECOND)
        return (tv.tv_sec * 1000000 + tv.tv_usec);
    else
        error_exit("Invalid time code provided to get_time_in_ms function.");

    return (1337);

}


/*
 * precision_sleep pauses execution for a given time in ms.
 * It loops with short sleeps for better accuracy than usleep().
 * Used to simulate actions like eating, sleeping, and thinking.
 * 01: Get the current time in milliseconds at the start of the sleep.
*/
void precision_usleep(long duration_in_ms, t_table *table) {
    long start_time ;
    long elapsed_time;
    long remaining_time;
    
    start_time = get_time_in_ms(MILLISECOND);
    while (get_time_in_ms(MILLISECOND) - start_time < duration_in_ms) {
        if (simulation_end(table)) // Check if the simulation has ended to avoid unnecessary sleeping.
            break;
        elapsed_time = get_time_in_ms(MILLISECOND) - start_time;
        remaining_time = duration_in_ms - elapsed_time;
        if (remaining_time > 1000) 
            usleep(duration_in_ms / 2); // Sleep for the remaining time in microseconds
        else
        {
            while (get_time_in_ms(MILLISECOND) - start_time < duration_in_ms) {
                if (simulation_end(table)) // Check if the simulation has ended to avoid unnecessary sleeping.
                    break;
                usleep(100); // Sleep for a short time to avoid busy waiting
            }
        }
            

    }
}
