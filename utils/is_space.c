#include "philo.h"

/* 
 * To check if a character is a whitespace character (space, tab, newline, etc.). 
 * This function will be used in the ft_atol function to skip leading whitespace characters when converting a string to a long integer. 
 * The function returns true if the character is a whitespace character and false otherwise.
*/
int is_space(char c) {
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}