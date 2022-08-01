# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 04:59:55 by hkhalil           #+#    #+#              #
#    Updated: 2022/08/01 18:52:22 by hkhalil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = philo.c check_for_errors.c utils.c utils1.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
