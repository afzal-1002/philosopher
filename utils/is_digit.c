#include "philo.h"
#include <ctype.h>

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
    if (isdigit((unsigned char)*str))
        return 1;
    error_exit(RED "Input string contains non-digit characters." RESET);
    return 0;
}

/*
 * is_digit_space: non-fatal check that returns:
 *  1  -> character is a digit
 * -1  -> character is a space (isspace)
 *  0  -> NUL terminator (empty)
 * On NULL or an invalid character, it calls error_exit.
 */
int is_digit_space(const char *str) {
    if (str == NULL) {
        error_exit(RED "Input string is NULL." RESET);
        return 0;
    }
    if (*str == '\0')
        return 0;
    if (isspace((unsigned char)*str))
        return -1;
    if (isdigit((unsigned char)*str))
        return 1;
    error_exit(RED "Input string contains non-digit characters." RESET);
    return 0;
}
