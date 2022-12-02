CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

NAME = philo_bonus
SRCS = free_bonus.c \
		init_bonus.c \
		lets_eat_bonus.c \
		philosopher_bonus.c \
		time_bonus.c \
		utils_bonus.c

OBJS = $(SRCS:%.c=%.o)
INCLUDES = -I./

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : clean fclean re all