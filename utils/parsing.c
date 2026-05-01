#include "philo.h"


/*  
 *  Converts a string to a long integer. It handles optional leading whitespace, an optional sign, and numeric characters. 
 *  The function returns the converted long integer value. If the input string is invalid 
 * (e.g., contains non-digit characters, is too long, or represents a number outside the range of a long integer), 
 * the function will print an error message and exit the program.
*/
long ft_atol(const char *str);

/*  utils.c contains utility functions for the dining philosophers simulation.
 *  It includes error handling and input parsing to keep the code modular.
 *  The print_error function displays error messages in a consistent format.
 *  The parse_input function validates and parses command-line arguments.
 *  Program usage:
 *      ./philo num_philos time_to_die time_to_eat time_to_sleep [meals_required]
 *  The main function checks the number of arguments before calling parse_input.
 *  The parse_input function converts arguments from strings to numerical values
 *  and initializes the shared table structure.
*/

void parse_input(char **argv, t_table *table);

/*  Check for negative values and zero for the time parameters, as they are not valid in the context of the dining philosophers simulation. 
 * If any of the parameters are invalid, the function will print an error message and exit the program.
 * Check if the number is valid.
 * Check the length of the number, as it should not exceed the limits of a long integer. 
 * If the input is too long, it may indicate an invalid number, and the function will print an error message and exit the program.
 * Check for INT_MAX and INT_MIN, as they are not valid in the context of the dining philosophers simulation. 
 * If any of the parameters are invalid, the function will print an error message and exit the program.
 * Function returns a char to indicate if the input is valid or not. 
 * It returns 1 (true) if valid, and 0 (false) if invalid after printing an error message and exiting
 *  the program.
 * ./philo 5 800 200 200 7
*/
char *validate_input(const char *str);



void parse_input(char **argv, t_table *table) {

        table->num_philos = ft_atol(argv[1]);
        table->time_to_die = ft_atol(argv[2]) * 1000;
        table->time_to_eat = ft_atol(argv[3]) * 1000; 
        table->time_to_sleep = ft_atol(argv[4]) * 1000; 

        if(table->time_to_die < 6e4 || table->time_to_eat < 60000 || table->time_to_sleep < 60000)
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

    // Convert characters to long
    while (is_digit(*str)) {
        number = number * 10 + (*str - '0');
        str++;
    }

    if (number > INT_MAX) 
        error_exit( GREEN "Input number is too large to be a valid long integer." RESET);
    
    return (number);
}


char *validate_input(const char *str) {

    int len = 0;
    const char *number;


    while(is_space(*str))
        str++;

     if (*str == '+') 
        str++; 
    else if (*str == '-') 
        error_exit(GREEN "Negative values are not allowed for time parameters." RESET);

    if(!is_digit(str))
        error_exit(GREEN "Input string contains non-digit characters." RESET);

    number = str;
    while(is_digit(*str++)) 
        len++;

    if (len == 0)
        error_exit("Input string does not contain any digits.");
    if(len > 10)
        error_exit(RED "Input string is too long to be a valid long integer." RESET);

    return (number);
}