#include "philo.h"

/********** TLDR of the dining philosophers problem **********
 * The dining philosophers problem is a classic synchronization problem that illustrates the challenges of resource sharing and deadlock prevention in concurrent programming. 
 * In this problem, a certain number of philosophers sit around a circular table, and there is a fork between each pair of adjacent philosophers. 
 * Each philosopher alternates between thinking and eating. To eat, a philosopher needs to pick up both the left and right forks. 
 * The challenge is to design a protocol that allows the philosophers to eat without causing deadlock (where all philosophers are waiting indefinitely for each other) or starvation (where a philosopher never gets to eat).
 * The main goals are to ensure that all philosophers can eat without getting stuck in a deadlock and to prevent any philosopher from starving.
 * Common solutions involve using mutexes or semaphores to control access to the forks and implementing strategies such as resource hierarchy or allowing only a certain number of philosophers to eat at the same time.
 * The dining philosophers problem serves as an important example in understanding synchronization issues and designing concurrent algorithms.
*/

void set_bool_value(t_mutex *mutex, bool *flag, bool value);
bool get_bool_value(t_mutex *mutex, bool *value);
bool simulation_start(t_table *table);
bool simulation_end(t_table *table);
bool is_simulation_start(t_table *table);
void set_long_value(t_mutex *mutex, long *var, long value);

void set_bool_value(t_mutex *mutex, bool *flag, bool value) {
    safe_mutex_handler(mutex, LOCK);
    *flag = value;
    safe_mutex_handler(mutex, UNLOCK);
}

bool get_bool_value(t_mutex *mutex, bool *value) {
    bool flag;
    safe_mutex_handler(mutex, LOCK);
    flag = *value;
    safe_mutex_handler(mutex, UNLOCK);
    return (flag);

}

void set_long_value(t_mutex *mutex, long *var, long value) {
    safe_mutex_handler(mutex, LOCK);
    *var = value;
    safe_mutex_handler(mutex, UNLOCK);
}


/*
 REDUNTANT CODE, IGNORE
*/

bool simulation_start(t_table *table) {
    return get_bool_value(&table->table_mutex, &table->all_thread_ready);
}

bool simulation_end(t_table *table) {
    return get_bool_value(&table->table_mutex, &table->simulation_should_end);
}

bool is_simulation_start(t_table *table) {
    return get_bool_value(&table->table_mutex, &table->all_thread_ready);
}
