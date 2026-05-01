#include "philo.h"

/*
 * is_digit: fatal predicate used by parsing helpers. Returns 1 if the
 * pointer points to a digit, otherwise prints error and exits.
 */
int is_digit(const char *str) {
    if (str == NULL) {
        error_exit(RED "Input string is NULL." RESET);
        return 0;
    }
    if (*str == '\0') {
        error_exit(RED "Input string is empty." RESET);
        return 0;
    }
    if (*str >= '0' && *str <= '9')
        return 1;
    error_exit(RED "Input string contains non-digit characters." RESET);
    return 0;
}


int is_digit_space(const char *str) {
    if (str == NULL) {
        error_exit(RED "Input string is NULL." RESET);
        return 0;
    }
    if (*str == '\0')
        return 0;
    if (is_space(*str))
        return -1;
    if (*str >= '0' && *str <= '9')
        return 1;
    error_exit(RED "Input string contains non-digit characters." RESET);
    return 0;
}
