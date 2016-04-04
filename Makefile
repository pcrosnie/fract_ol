# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/20 12:13:09 by pcrosnie          #+#    #+#              #
#    Updated: 2016/04/04 14:55:15 by pcrosnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FLAGS = -Wall -Werror -Wextra -L /usr/lib -lmlx -framework OpenGl -framework AppKit

SRC = libft/libft.a main.c ft_mandelbrot.c ft_julia.c ft_newton_fract.c

all: $(NAME)

$(NAME):
	make -C libft/
	gcc -o $(NAME) $(FLAGS) $(SRC)

clean:
	make -C libft/ fclean
		
fclean: clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY: all clean fclean re
