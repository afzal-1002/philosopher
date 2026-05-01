#include "philo.h"

/* Thread wrappers and error handling for create/join/detach. */
void handler_thread_error(int status, t_opcode opcode);

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
        error_exit("No resources available to create another thread.");
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