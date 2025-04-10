NAME = philo
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread -pthread

SRCS = philo.c times.c routine.c arg_check.c init_all.c utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

main:
	make re
	make clean
	clear

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:  all clean fclean re