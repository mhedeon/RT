# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 15:37:02 by mhedeon           #+#    #+#              #
#    Updated: 2019/02/28 19:06:05 by mhedeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = main.c vector.c window.c intersect.c normal.c scene.c camera.c \
	object.c read.c light.c init.c trace.c trash.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I./frameworks/SDL2.framework/Headers/ \
			-F./frameworks -I./libft

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@gcc -g -o $(NAME) $(OBJ) $(FRAMEWORKS) -L./libft -lft

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@rm -f $(OBJ)

re: fclean all
	@make -C libft re