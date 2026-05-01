#include "philo.h"

/* Return 1 when c is ASCII whitespace; otherwise return 0. */
int is_space(char c) {
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}