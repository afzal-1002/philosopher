#include "philo.h"


void error_exit(const char *message);
long get_time_in_ms(t_time_code time_code);
void precision_usleep(long duration_in_ms, t_table *table);

void error_exit(const char *message) {
    printf(RED "%s \n" RESET , message);
    exit(EXIT_FAILURE);
}

/* Return current time in seconds, milliseconds, or microseconds. */
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


/* Sleep with periodic checks so simulation can stop promptly. */
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
        if (remaining_time > 1)
            usleep(remaining_time * 1000);
        else
            usleep(100);

    }
}
