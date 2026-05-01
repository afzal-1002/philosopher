#include "philo.h"

/*
 * if input is valid, the function will return 1 (true), and if the input is invalid.
 * Tthe function will return 0 (false) after printing an error message and exiting the program.
*/
int is_digit(const char *str) {
    if(str == NULL || *str == '\0') {
        error_exit(RED "Input string is empty." RESET);
        return 0;
    }

    if(str >= '0' && str <= '9') {
        return 1;
    } else {
        error_exit(RED "Input string contains non-digit characters." RESET);
        return 0;
    }
}
