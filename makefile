NAME=minishell
CC=gcc
CFLAGS=-g -Ilibft -Wall -Werror -Wextra
SRC=main.c \
	minishell.c \
	parse.c \
	builtin.c \
	msh_error.c \
	msh_env.c \
	set_msh.c \
	cmd.c \
	signal_handler.c
OBJ=$(SRC:.c=.o)
.PHONY: test

all: $(NAME)

$(NAME): $(OBJ) libft.a
	gcc $(OBJ) -o $(NAME) libft/libft.a

$(OBJ): minishell.h

libft.a:
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
