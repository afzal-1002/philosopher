#include "philo.h"
#include <ctype.h>


/*  Converts a string to a long integer. It handles optional leading whitespace, an optional sign, and numeric characters.
 *  The function returns the converted long integer value. If the input string is invalid
 *  (e.g., contains non-digit characters, is too long, or represents a number outside the range of a long integer),
 *  the function will print an error message and exit the program.
*/
long ft_atol(const char *str);


void parse_input(char **argv, t_table *table);

/* validate_input returns a pointer to the first numeric character in the input string. */
const char *validate_input(const char *str);


void parse_input(char **argv, t_table *table) {
    /* Diagnostic prints to identify which argument may be empty */
    table->num_philos = ft_atol(argv[1]);
    table->time_to_die = ft_atol(argv[2]);
    table->time_to_eat = ft_atol(argv[3]);
    table->time_to_sleep = ft_atol(argv[4]);

    if (table->time_to_die < 60 || table->time_to_eat < 60 || table->time_to_sleep < 60)
        error_exit("Time parameters must be at least 60 milliseconds.");

    if (argv[5])
        table->num_meals_required = ft_atol(argv[5]);
    else
        table->num_meals_required = -1;
}


long ft_atol(const char *str) {
    long number;

    number = 0;
    str = validate_input(str);

    while (*str != '\0' && isdigit((unsigned char)*str)) {
        number = number * 10 + (*str - '0');
        str++;
    }

    if (number > INT_MAX)
        error_exit(GREEN "Input number is too large to be a valid long integer." RESET);

    return (number);
}


const char *validate_input(const char *str) {

    int len = 0;
    const char *number;
    
    while (is_space(*str))
        str++;

    if (*str == '+')
        str++;
    else if (*str == '-')
        error_exit(GREEN "Negative values are not allowed for time parameters." RESET);

    if (!is_digit(str))
        error_exit(GREEN "Input string contains non-digit characters." RESET);

    number = str;
    while (is_digit_space(str) == 1) {
        len++;
        str++;
    }

    if (len == 0)
        error_exit("Input string does not contain any digits.");
    if (len > 10)
        error_exit(RED "Input string is too long to be a valid long integer." RESET);

    return (number);
}