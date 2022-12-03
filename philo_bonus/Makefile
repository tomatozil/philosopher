# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 19:01:31 by jiyun             #+#    #+#              #
#    Updated: 2022/12/02 19:01:36 by jiyun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

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
