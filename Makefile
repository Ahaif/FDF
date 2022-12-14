
CFLAGS = -Wall -Werror -Wextra

NAME = fdf

CC = cc 

SRC = fdf.c get_next_line.c get_next_line_utils.c read_maps.c ft_split.c ft_atoi.c tools.c tools2.c

OBJS = fdf.o get_next_line.o get_next_line_utils.o read_maps.o ft_split.o ft_atoi.o tools.o tools2.o

MLX = -lmlx -framework OpenGL -framework AppKit

INCLUDE = fdf.h

all : $(NAME)

$(NAME) : $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all