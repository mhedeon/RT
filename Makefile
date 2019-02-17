# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 15:37:02 by mhedeon           #+#    #+#              #
#    Updated: 2019/02/17 20:26:51 by mhedeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC = main.c vector.c window.c intersect.c objects.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I./frameworks/SDL2.framework/Headers/ \
			-I./frameworks/SDL2_image.framework/Headers/ \
			-I./frameworks/SDL2_mixer.framework/Headers/ \
			-I./frameworks/SDL2_ttf.framework/Headers/ \
			-F./frameworks -I./libft

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
												-framework SDL2_image \
												-framework SDL2_mixer \
												-framework SDL2_ttf

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