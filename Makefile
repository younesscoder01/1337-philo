# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 16:16:38 by ysahraou          #+#    #+#              #
#    Updated: 2024/10/13 10:46:54 by ysahraou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ====================================== variables ====================================== #
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=leak -g3
NAME = philo
SRC = src/philo.c src/check_args.c src/err.c src/init_and_free.c src/prints.c  src/get_rsrc.c \
	src/fork_actions.c 
OBJ = $(SRC:.c=.o)
RM = rm -rf
# ======================================================================================= #
# ====================================== rules ========================================== #
%.o: %.c inc/philo.h 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean: 
	$(RM) $(OBJ)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all
# ======================================================================================= #