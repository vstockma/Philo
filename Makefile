# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 11:21:25 by valentin          #+#    #+#              #
#    Updated: 2023/02/21 12:01:53 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRC = main.c free.c start.c

OBJ = $(SRC:.c=.o)

CFLAGS = -g -Wall -Werror -Wextra

CC = cc

RM = rm -f

.PHONY: all clean fclean re

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all