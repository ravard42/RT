# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbirtel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/24 19:23:36 by dbirtel           #+#    #+#              #
#    Updated: 2017/03/28 17:55:55 by dbirtel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmath.a

SRC = vec_len.c\
	  dot.c\
	  add_coord.c\
	  sub_coord.c\
	  mult_coord.c\
	  translate.c\
	  vec_norm.c\
	  cross.c\
	  magnitude_qt.c\
	  norm_qt.c\
	  inv_qt.c\
	  rot_qt.c\
	  mult_qt.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O2

all : $(NAME)
	@echo "\033[32m◊\033[0m libmath ready"

$(NAME) : $(OBJ) libmath.h
		$(CC) $(CFLAGS) -c $(SRC)
		ar rc $(NAME) $(OBJ)

clean :
		rm -f $(OBJ)

fclean : clean
		rm -f $(NAME)

re : fclean all
