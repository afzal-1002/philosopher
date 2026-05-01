#include "philo.h"

void error_exit(const char *message) {
    printf(RED "%s \n" RESET , message);
    exit(EXIT_FAILURE);
}