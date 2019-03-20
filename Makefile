#******************************************************************************#
#                ___                                                           #
#               /  /\    ___                        authors:                   #
#              /  /::\  /__/\                 ┌┬┐┬ ┬┌─┐┌┬┐┌─┐┌─┐┌┐┌            #
#             /  /:/\:\ \  \:\                │││├─┤├┤  ││├┤ │ ││││            #
#            /  /::\ \:\ \__\:\               ┴ ┴┴ ┴└─┘─┴┘└─┘└─┘┘└┘            #
#           /__/:/\:\_\:\/  /::\              ┬┬┌─┌─┐┬  ┌─┐┌─┐┬ ┬┬ ┬           #
#           \__\/~|::\/:/  /:/\:\             │├┴┐│ ││  │ │└─┐├─┤└┬┘           #
#              |  |:|::/  /:/__\/             ┴┴ ┴└─┘┴─┘└─┘└─┘┴ ┴ ┴            #
#              |  |:|\/__/:/                  ┌─┐┌─┐┌┐ ┌┬┐┬ ┬┬  ┬  ┌─┐         #
#              |__|:|~\__\/                   ├─┤├─┤├┴┐ │││ ││  │  ├─┤         #
#               \__\|                         ┴ ┴┴ ┴└─┘─┴┘└─┘┴─┘┴─┘┴ ┴         #
#                                                                              #
#******************************************************************************#

NAME	=	RT
OBJDIR	=	./obj/
SRCDIR	=	./src/
INCDIR	=	./includes/
LIBFT	=	-lft -L./libft/

SRC =	main.c \
		vector.c \
		window.c \
		intersect.c \
		normal.c \
		scene.c \
		camera.c \
		object.c \
		read.c \
		light.c \
		init.c \
		trace.c \
		trash.c \

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

FLAGS = -Wall -Werror -Wextra

INCLUDES =	-I./frameworks/SDL2.framework/Headers/ 

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 

all: obj $(NAME)

obj:
	@ mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	@ make -C libft
	@ gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) -I $(INCDIR) $(FRAMEWORKS)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@ gcc $(FLAGS) -I $(INCDIR) -c -o $@ $<

clean:
	@ make clean -C libft 
	@ /bin/rm -rf $(OBJDIR)

fclean: clean
	@ make fclean -C libft
	@ /bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
