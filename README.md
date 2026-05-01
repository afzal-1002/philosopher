*This project has been created as part of the 42 curriculum by mafzal.*

# Dining Philosophers

A concurrent simulation of the classic Dining Philosophers synchronization problem using POSIX threads and mutexes.

## Description

The Dining Philosophers problem is a classic synchronization problem that illustrates challenges in concurrent programming. This project implements a solution where philosophers sit at a round table with forks between them. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must acquire both adjacent forks (mutexes), creating potential for deadlock and starvation. The simulation demonstrates proper use of mutexes and thread synchronization to prevent these issues.

**Goal**: Implement a deadlock-free solution where all philosophers can eat and no one starves, using POSIX threads and mutexes.

## Instructions

### Compilation

```bash
make
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die` (ms): Time before starvation if eating hasn't started
- `time_to_eat` (ms): Duration of eating
- `time_to_sleep` (ms): Duration of sleeping
- `[number_of_times_each_philosopher_must_eat]` (optional): Stop condition (all philosophers must eat this many times)

**Examples:**

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 410 200 200
```

### Project Structure

- **Main**: Parses input, initializes data structures, spawns philosopher threads and monitor
- **Philosopher threads**: Execute eat → sleep → think cycle
- **Monitor thread**: Detects philosopher death and signals simulation end
- **Synchronization**: Mutexes protect forks, shared state, and output

### Specifications

**Program name:** `philo`

**Allowed external functions:**
`memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

**Global variables:** Forbidden

**No data races:** All shared state protected by mutexes

## Resources

### Classic References

- **Dining Philosophers Problem**: Dijkstra, E. W. (1971). "Hierarchical ordering of sequential processes"
- **POSIX Threads Documentation**: https://man7.org/linux/man-pages/man7/pthreads.7.html
- **Mutex Synchronization**: https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html
- **Deadlock Prevention**: Classic OS textbook approaches to resource allocation and circular wait prevention

### AI Usage

AI assistance was used for:
- **Code structure and organization**: Helped design the overall architecture of threads, synchronization primitives, and module layout
- **Debugging timing and synchronization issues**: Identified race conditions and suggested proper mutex placement
- **Understanding spec requirements**: Clarified 42 project constraints and pthread API semantics
- **Code review**: Validated correctness of mutex locking patterns and thread lifecycle management

AI-generated code was thoroughly tested, understood, and validated before integration. All critical synchronization logic was peer-reviewed and adapted based on specific project constraints.

## Architecture

- **philo.h**: Central header with type definitions, enums, and function prototypes
- **philo.c**: Main entry point, argument parsing
- **init.c**: Memory allocation and initialization
- **utils/dining.c**: Philosopher thread routine and main simulation loop
- **utils/dining_utils.c**: Philosopher actions (eating, sleeping, thinking)
- **utils/monitor.c**: Death detection and simulation end conditions
- **utils/parsing.c**: Argument validation and conversion
- **utils/is_digit.c, utils/is_space.c**: Character validation helpers
- **utils/lock_unlock.c**: Thread-safe state accessors
- **utils/syncro_utils.c**: Synchronization helpers
- **utils/thread_safe.c, utils/mutex_safe.c**: Error handling wrappers
- **utils/utils.c**: Time and sleep utilities
- **utils/write_mutex.c**: Thread-safe output
- **utils/cleanup.c**: Resource deallocation
