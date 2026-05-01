#include "philo.h"

/*  Handles thread-related errors based on the returned status and operation type.
 *  If status is 0, the function returns without error.
 *  Checks for EAGAIN when system resources are insufficient to create a new thread.
 *  Checks for EPERM when the caller lacks permission to set thread scheduling parameters.
 *  Checks for EINVAL during CREATE operation for invalid thread attributes.
 *  Checks for ESRCH when the specified thread cannot be found.
 *  Checks for EINVAL during JOIN or DETACH when the thread reference is invalid.
 *  Checks for EDEADLK when a deadlock is detected or a thread attempts to join itself.
 *  Checks for EINVAL when the thread is not joinable.
 *  Calls error_exit with an appropriate message for each error case.
*/
void handler_thread_error(int status, t_opcode opcode);

/*  Provides a safe interface for handling thread operations.
 *  Supports CREATE, JOIN, and DETACH operations based on the opcode.
 *  For CREATE, it initializes a new thread with the given start routine and data.
 *  For JOIN, it waits for the specified thread to finish execution.
 *  For DETACH, it detaches the thread to release resources automatically.
 *  Calls handler_thread_error to validate the result of each operation.
 *  If an invalid opcode is provided, the function will print an error message and exit the program.
*/
void safe_thread_handler(pthread_t *thread, void *(*start_routine)(void *),
    void *data, t_opcode opcode);


void safe_thread_handler(pthread_t *thread, void *(*start_routine)(void *), void *data, t_opcode opcode) {
    if(CREATE == opcode)
        handler_thread_error(pthread_create(thread, NULL, start_routine, data), opcode);
    else if(JOIN == opcode)
        handler_thread_error(pthread_join(*thread, NULL), opcode);
    else if(DETACH == opcode)  
        handler_thread_error(pthread_detach(*thread), opcode);
    else 
        error_exit("Invalid opcode for thread handler: must be CREATE, JOIN, or DETACH.");
}

void handler_thread_error(int status, t_opcode opcode) {

    if (status == 0)
        return;

    if(status == EAGAIN)
        eror_exit("No resources available to create another thread.");
     else if(status == EPERM)
        error_exit("The caller does not have appropriate permission to set the scheduling policy and parameters specified in attr.");
    else if(status == EINVAL && opcode == CREATE)
        error_exit("The value specified by attr is invalid for thread creation.");
     else if(status == ESRCH)
        error_exit("No thread could be found corresponding to that specified by thread.");
     else if(status == EINVAL && (opcode == JOIN || opcode == DETACH))
        error_exit("The value specified by thread is invalid for join/detach operation.");
     else if(status == EDEADLK)
        error_exit("A deadlock was detected or the thread tried to join itself.");
     else if(status == EINVAL)
        error_exit("Thread is not a joinable thread.");
}