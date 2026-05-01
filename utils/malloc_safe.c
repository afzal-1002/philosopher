#include "philo.h"

/* Allocate memory or exit on failure/invalid size. */
void *safe_malloc(size_t size)
{
    void    *ptr;

    if (size == 0)
        error_exit("Invalid allocation size.");

    ptr = malloc(size);
    if (ptr == NULL)
        error_exit("Memory allocation failed.");
    return (ptr);
}