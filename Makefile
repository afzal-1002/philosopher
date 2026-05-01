GCC= gcc
CFLAGS= -Wall -Wextra -Werror -pthread -I.
SRCS= philo.c \
	  init.c \
	  utils/dining.c \
	  utils/dining_utils.c \
	  utils/is_digit.c \
	  utils/is_space.c \
	  utils/lock_unlock.c \
	  utils/malloc_safe.c \
	  utils/mutex_safe.c \
	  utils/parsing.c \
	  utils/syncro_utils.c \
	  utils/monitor.c \
	  utils/thread_safe.c \
	  utils/utils.c \
	  utils/write_mutex.c \
	  utils/cleanup.c \

	
OBJS= $(SRCS:.c=.o)
NAME= philo

all: $(NAME)

$(NAME): $(OBJS)
	$(GCC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re