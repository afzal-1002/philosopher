#include "philo.h"

/* Thread-safe accessors for shared table/philosopher state. */

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

long get_long_value(t_mutex *mutex, long *var) {
    long value;

    safe_mutex_handler(mutex, LOCK);
    value = *var;
    safe_mutex_handler(mutex, UNLOCK);
    return (value);
}

/* Compatibility wrappers used by synchronization helpers. */

bool simulation_start(t_table *table) {
    return get_bool_value(&table->table_mutex, &table->all_thread_ready);
}

bool simulation_end(t_table *table) {
    return get_bool_value(&table->table_mutex, &table->simulation_should_end);
}

bool is_simulation_start(t_table *table) {
    return get_bool_value(&table->table_mutex, &table->all_thread_ready);
}
