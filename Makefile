# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/29 13:10:57 by xuwang            #+#    #+#              #
#    Updated: 2021/08/04 13:55:34 by xuwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGE = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC := srcs/main.c \
		srcs/utils.c \
		srcs/init.c \
		srcs/philo.c \
		srcs/check.c 

OBJ := $(SRC:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGE) -I. -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGE) $(OBJ) -I. -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ)
	
fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re