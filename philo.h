#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> // For printf
#include <stdlib.h> // For malloc, free
#include <unistd.h> // For fork, sleep, write
#include <sys/types.h> // For pid_t
#include <sys/wait.h> // For waitpid
#include <sys/time.h> // For gettimeofday
#include <stdbool.h> // For bool type
#include <pthread.h> // For mutex init destroy lock unlock Thread: create join detach
#include <limits.h> // For INT_MAX
#include <errno.h> // For error handling


/* ./philo num_philos time_to_die time_to_eat time_to_sleep [meals_required] */


/* Types */
typedef pthread_mutex_t t_mutex;
typedef struct s_table t_table;
typedef struct s_fork t_fork;
typedef struct s_philo t_philo;


// ANSI escape codes for terminal output colors.

#define RED "\033[31m" // Red color
#define GREEN "\033[32m" // Green color
#define YELLOW "\033[33m" // Yellow color
#define BLUE "\033[34m" // Blue color
#define MAGENTA "\033[35m" // Magenta color
#define CYAN "\033[36m" // Cyan color
#define RESET "\033[0m" // Reset color
#define WHITE "\033[37m" // White color for regular messages
#define ERROR_COLOR RED
#define ERROR_RESET RESET

#define DEBUG_MODE 0 // Set to 1 to enable debug mode, 0 to disable



/* Opcodes for mutex/thread handlers */
typedef enum e_opcode {
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,

} t_opcode;


/* Time unit selector */
typedef enum e_time_code {
    SECOND,
    MILLISECOND,
    MICROSECOND
} t_time_code;


/* Philosopher states */
typedef enum e_philo_status {

    EATING,
    SLEEPING,
    THINKING,
    TAKEN_FIRST_FORK,
    TAKEN_SECOND_FORK,
    DEAD
} t_philo_status;


/* Structures */

typedef struct  s_fork
{
    int fork_id;
    t_mutex fork;

} t_fork;



/* Philosopher */
typedef struct s_philo{
    int ph_id; // Philosopher ID
    long meals_counter; // Counter for the number of meals eaten by the philosopher
    bool full; // Flag to indicate if the philosopher is full (has eaten enough)
    long last_meal_time; // Time of the last meal in milliseconds
    t_fork *first_fork;  // Pointers to the left and right forks
    t_fork *second_fork; // Pointers to the left and right forks
    pthread_t thread_id; // Thread ID for the philosopher's thread
    t_mutex philo_mutex; // Mutex for synchronizing access to philosopher's data (race conditions)
    t_table *table; // Pointer to the shared table structure

} t_philo;


/* Shared table state */
typedef struct s_table{
    long num_philos; // Number of philosophers
    long time_to_die; // Time to die in milliseconds
    long time_to_eat; // Time to eat in milliseconds
    long time_to_sleep; // Time to sleep in milliseconds
    long num_meals_required; // Number of meals required for each philosopher to be considered full
    long simulation_start_time; // Time when the simulation starts in milliseconds
    long simulation_end_time; // Time when the simulation ends in milliseconds
    long thread_running_count; // Counter for the number of philosopher threads currently running
    bool all_thread_ready; // Flag to indicate if all philosophers are ready to start
    bool simulation_should_end; // Flag to indicate if the simulation should end (someone died or all full)
    t_mutex table_mutex; // Protects shared table fields
    t_mutex write_mutex; // Mutex for synchronizing print statements
    pthread_t monitor; // Thread ID for the monitor thread
    t_philo *philos; // Array of philosophers
    t_fork *forks; // Array of forks

} t_table;



/* Function prototypes */
/* parsing.c */
int is_space(char c);
int is_digit(const char *str);
int is_digit_space(const char *str);
long ft_atol(const char *str);
void parse_input(char **argv, t_table *table);
const char *validate_input(const char *str);


/* safe helpers */
void *safe_malloc(size_t size);
void safe_mutex_handler(t_mutex *mutex, t_opcode opcode);
void handler_mutex_error(int status, t_opcode opcode);
void safe_thread_handler(pthread_t *thread, void *(*start_routine)(void *), void *data, t_opcode opcode);
void handler_thread_error(int status, t_opcode opcode);

/* init.c */
void philo_init(t_table *table) ;
void data_init(t_table *table) ;
void assign_forks(t_philo *philo, t_fork *forks, int index);

/* lock_unlock.c */
void set_bool_value(t_mutex *mutex, bool *flag, bool value);
void set_long_value(t_mutex *mutex, long *var, long value);
long get_long_value(t_mutex *mutex, long *var);
bool get_bool_value(t_mutex *mutex, bool *value);
bool simulation_start(t_table *table);
bool simulation_end(t_table *table);
bool is_simulation_start(t_table *table);
void wait_all_thread_ready(t_table *table);



/* dining.c / dining_utils.c */
void *dinner_simulation(void *data);
void dinner_start(t_table *table);
void dinner_philosophers(t_table *table);
void eating(t_philo *philo);
void thinking(t_philo *philo, bool pre_simulation);
void sleeping(t_philo *philo);
void cleanup(t_table *table);
/* de_synchronization_philosopher_monitor removed: startup staggering was moved/disabled. */



/* utils.c */
void error_exit(const char *message);
long get_time_in_ms(t_time_code time_code);
void precision_usleep(long duration_in_ms, t_table *table);



/* write_mutex.c */
void write_mutex(t_philo_status status, t_philo *philo, bool debug);
void write_status_debug(t_philo_status status, t_philo *philo, long elasped_time);

/* syncro_utils.c function prototypes */
void wait_all_thread_ready(t_table *table);
void increment_long(t_mutex *mutex, long *validate_input);
bool all_thread_running(t_mutex *mutex, long *thread_running_count, long num_philos);

/* monitor.c function prototypes */
void *monitor_dinner(void *data);
bool philo_is_dead(t_philo *philo);


#endif
