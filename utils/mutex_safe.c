#include "philo.h"

/*  Mutex handler for LOCK, UNLOCK, INIT, DESTROY operations.
 *  Calls handler_mutex_error to validate the result of each operation.
 *  If an invalid opcode is provided, the function will print an error message and exit the program.
*/
void safe_mutex_handler(t_mutex *mutex, t_opcode opcode) {
    if (LOCK == opcode)
        handler_mutex_error(pthread_mutex_lock(mutex), opcode);
    else if (UNLOCK == opcode)
        handler_mutex_error(pthread_mutex_unlock(mutex), opcode);
    else if (INIT == opcode)
        handler_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
    else if (DESTROY == opcode)
        handler_mutex_error(pthread_mutex_destroy(mutex), opcode);
    else
        error_exit("Invalid opcode for mutex handler.");
}

/*  Handles mutex-related errors based on the returned status and operation type.
 *  If status is 0, the function returns without error.
 *  Checks for EINVAL when performing LOCK or UNLOCK operations.
 *  Checks for EINVAL during INIT operation for invalid attributes.
 *  Checks for EDEADLK to detect deadlock conditions during LOCK or UNLOCK.
 *  Checks for EBUSY when attempting to destroy a locked mutex.
 *  Checks for ENOMEM when memory allocation for mutex fails.
 *  Calls error_exit with an appropriate message for each error case.
*/
void handler_mutex_error(int status, t_opcode opcode) {
    if (status == 0)
        return;
    if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
        error_exit("The value specified by mutex is invalid for lock/unlock operation.");
    else if (status == EINVAL && opcode == INIT)
        error_exit("The value specified by attr is invalid for initialization.");
    else if (EDEADLK == status && opcode == LOCK)
        error_exit("A deadlock condition was detected when trying to lock the mutex.");
    else if (status == EDEADLK)
        error_exit("A deadlock condition was detected when trying to unlock the mutex.");
    else if (status == EBUSY)
        error_exit("The mutex is currently locked and cannot be destroyed.");
    else if (status == ENOMEM)
        error_exit("The process can not allocate enough memory for the mutex.");
}