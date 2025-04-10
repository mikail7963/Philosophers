NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror -g
CC = cc

SRCS =	philo_bonus.c \
		times_bonus.c \
		arg_check_bonus.c \
		routine_bonus.c \
		init_all_bonus.c  

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:  all clean fclean re