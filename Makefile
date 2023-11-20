NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBS = -lreadline
SRC = minishell.c	\
	utils.c	\
	dollar.c	\
	token.c	\
	exec.c	\
	ft_split.c	\
	ft_isbuiltin.c	\
	ft_heredoc.c	\
	builtins2.c	\
	builtins.c \
	builtins3.c \
	dollarutils.c \
	executils.c \
	executils2.c \
	exit.c \
	ft_cd.c \
	ft_export.c \
	ft_lexor.c \
	lexorutils.c \
	lexorutils2.c \
	tokenutils.c \
	utils2.c \
	utils3.c \
	
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
