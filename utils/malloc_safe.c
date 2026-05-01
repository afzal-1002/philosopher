#include "philo.h"

/*
 *  malloc and free functions will be used to allocate and deallocate memory for the philosophers and forks. 
*/

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