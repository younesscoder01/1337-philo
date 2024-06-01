# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 16:16:38 by ysahraou          #+#    #+#              #
#    Updated: 2024/06/01 16:24:02 by ysahraou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC = src/philo.c
OBJ = $(SRC:.c=.o)
RM = rm -rf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean: 
	$(RM) $(OBJ)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all