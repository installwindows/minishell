NAME=minishell
SRC=shell.c

.PHONY: test

all: $(NAME)

$(NAME):
	gcc $(SRC) -o $(NAME) libft.a libftprintf.a

fclean:
	rm -rf $(NAME)

re: fclean all

t:
	gcc $(SRC) -o $(NAME) libft.a libftprintf.a -g
