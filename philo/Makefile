# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 18:59:40 by jiyun             #+#    #+#              #
#    Updated: 2022/12/02 18:59:46 by jiyun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread

NAME = philo
SRCS = free.c \
		init.c \
		lets_eat.c \
		philosopher.c \
		time.c \
		utils.c

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
