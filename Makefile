NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
LIBS = -lreadline
SRC = minishell.c	\
	utils.c	\
	dollar.c	\
	token.c	\
	exec.c	\
	ft_split.c	\
	ft_isbuiltin.c	\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
