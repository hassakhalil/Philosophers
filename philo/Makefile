# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhalil <hkhalil@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 04:59:55 by hkhalil           #+#    #+#              #
#    Updated: 2022/06/20 16:38:06 by hkhalil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = philo.c check_for_errors.c utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all