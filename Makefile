# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 15:37:02 by mhedeon           #+#    #+#              #
#    Updated: 2019/03/27 16:36:33 by ikoloshy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = src/main.c src/vector.c src/window.c src/intersect.c src/normal.c \
	  src/scene.c src/camera.c src/object.c src/read.c src/light.c src/init.c \
	 src/trace.c src/trash.c src/slice.c

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
