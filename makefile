NAME=minishell
CC=gcc
CFLAGS=-g -Ilibft
SRC=main.c \
	minishell.c \
	parse.c \
	builtin.c \
	msh_error.c \
	msh_env.c \
	ft_strcjoin.c
OBJ=$(SRC:.c=.o)
.PHONY: test

all: $(NAME)

$(NAME): $(OBJ) libft.a minishell.h
	gcc $(OBJ) -o $(NAME) libft/libft.a

libft.a:
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean:
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
