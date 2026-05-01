# philo

Dining Philosophers project (mandatory part) from 42.

MAIN:
    parse input
    init forks
    init philosophers
    create threads
    start monitor

THREAD:
    loop:
        take forks (odd/even logic)
        eat
        release forks
        sleep
        think

MONITOR:
    check death
    stop program



fork:  
    Fork is a mutex an array of mutex

Array of Philosiphor:   Which has data variabliable
    

## Mandatory Specifications

Program name: `philo`

Files to submit:
- `Makefile`
- `*.h`
- `*.c`
- inside directory `philo/`

Makefile targets:
- `NAME`
- `all`
- `clean`
- `fclean`
- `re`

Arguments:
1. `number_of_philosophers`
2. `time_to_die`
3. `time_to_eat`
4. `time_to_sleep`
5. `[number_of_times_each_philosopher_must_eat]` (optional)

Allowed external functions:
- `memset`
- `printf`
- `malloc`
- `free`
- `write`
- `usleep`
- `gettimeofday`
- `pthread_create`
- `pthread_detach`
- `pthread_join`
- `pthread_mutex_init`
- `pthread_mutex_destroy`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`

Libft: not authorized

Description: philosophers with threads and mutexes.

## Build

```bash
make
```

## Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
```

Example:

```bash
./philo 5 800 200 200
```

With optional meal limit:

```bash
./philo 5 800 200 200 7
```
# philosopher
