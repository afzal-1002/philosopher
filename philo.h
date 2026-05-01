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


/* 
* ./phiilo 5 800 200 200 [5]
*/

// ANSI Escape Codes for colored output
// pirntf(RED "This text will be red" RESET);
// fprintf(GREEN "This text will be green" RESET);

#define RED "\033[31m" // Red color
#define GREEN "\033[32m" // Green color
#define YELLOW "\033[33m" // Yellow color
#define BLUE "\033[34m" // Blue color
#define MAGENTA "\033[35m" // Magenta color
#define CYAN "\033[36m" // Cyan color
#define RESET "\033[0m" // Reset color Define for error messages
#define ERROR_COLOR RED
#define ERROR_RESET RESET



/*
    OPCODE Mutex and Thread Functions:
*/
typedef enum e_opcode {
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,

} t_opcode;



//** Defines **/
typedef pthread_mutex_t t_mutex;
typedef struct s_table t_table;
typedef struct s_fork t_fork;
typedef struct s_philo t_philo;

//** Structures ***

typedef struct  s_fork
{
    int fork_id;
    t_mutex fork;

} t_fork;



// Philosopher
typedef struct s_philo{
    int ph_id; // Philosopher ID
    long meals_counter; // Counter for the number of meals eaten by the philosopher
    bool full; // Flag to indicate if the philosopher is full (has eaten enough)
    long last_meal_time; // Time of the last meal in milliseconds
    t_fork *first_fork;  // Pointers to the left and right forks
    t_fork *second_fork; // Pointers to the left and right forks
    pthread_t thread_id; // Thread ID for the philosopher's thread
    t_table *table; // Pointer to the shared table structure

} t_philo;


/* 
    Table 
    ./philo num_philos time_to_die time_to_eat time_to_sleep [meals_required]
*/
typedef struct s_table{
    long num_philos; // Number of philosophers
    long time_to_die; // Time to die in milliseconds
    long time_to_eat; // Time to eat in milliseconds
    long time_to_sleep; // Time to sleep in milliseconds
    long num_meals_required; // Number of meals required for each philosopher to be considered full
    long simulation_start_time; // Time when the simulation starts in milliseconds
    long simulation_end_time; // Time when the simulation ends in milliseconds
    bool all_thread_ready; // Flag to indicate if all philosophers are full
    t_mutex table_mutex; // Mutex for synchronizing print statements // avoid read/write conflicts when multiple threads print to the console at the same time
    t_philo *philos; // Array of philosophers
    t_fork *forks; // Array of forks

} t_table;



//** Function Prototypes **
/* parsing.c function prototypes   */
void error_exit(const char *message);
int is_space(char c);
int is_digit(const char *str);
long ft_atol(const char *str);
void parse_input(char **argv, t_table *table);
char *validate_input(const char *str);


/* safe functions prototypes */
void *safe_malloc(size_t size);
void safe_mutex_handler(t_mutex *mutex, t_opcode opcode);
void handler_mutex_error(int status, t_opcode opcode);
void safe_thread_handler(pthread_t *thread, void *(*start_routine)(void *), void *data, t_opcode opcode);
void handler_thread_error(int status, t_opcode opcode);

/* init.c function prototypes */
void philo_init(t_table *table) ;
void data_init(t_table *table) ;
void assign_forks(t_philo *philo, t_fork *forks, int index);

/* lock_unlock.c function prototypes */
void set_bool_value(t_mutex *mutex, bool *flag, bool value);
bool get_bool_value(t_mutex *mutex, bool *value);
bool simulation_start(t_table *table);
bool simulation_end(t_table *table);
bool is_simulation_start(t_table *table);
void wait_all_thread_ready(t_table *table);



/* Dinning philosophers problem function prototypes */
void dinner_philosophers(t_table *table);
void cleanup(t_table *table);
void *dinner_simulation(void *data);



#endif
