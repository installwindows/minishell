NAME=minishell
SRC=main.c \
	minishell.c \
	parse.c \
	ft_pathjoin.c \
	gnl.c

.PHONY: test

all: $(NAME)

$(NAME):
	gcc $(SRC) -o $(NAME) libft.a libftprintf.a

fclean:
	rm -rf $(NAME)

re: fclean all

t:
	gcc -g $(SRC) -o $(NAME) libft.a libftprintf.a -g
