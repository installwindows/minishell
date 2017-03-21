/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 20:18:06 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 16:13:18 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"
#define FT_ISOK(c) (c == ' ' || c == '\t' || c == '\v' || c == '\r')

typedef struct	s_s
{
	char		*s;
	struct s_s	*next;
}				t_t;

static int		add(t_t ***c, char *str)
{
	**c = malloc(sizeof(t_t));
	(**c)->s = str;
	(**c)->next = NULL;
	*c = &(**c)->next;
	return (1);
}

static char		**toarray(t_t *l, int n)
{
	char	**arg;
	int		i;

	i = 0;
	arg = malloc(sizeof(char) * (n + 1));
	while (l)
	{
		arg[i++] = l->s;
		l = l->next;
	}
	arg[i] = NULL;
	return (arg);
}

char			**get_arg(const char *buf)
{
	t_t		*e;
	t_t		**c;
	int		n;
	int		j;
	int		i;

	i = 0;
	n = 0;
	e = NULL;
	c = &e;
	while (buf[i])
	{
		while (FT_ISOK(buf[i]))
			i++;
		if (buf[i] == '"' && (j = ft_strichr(&buf[i + 1], '"')) >= 0)
		{
			n += add(&c, ft_strsub(buf, ++i, j));
			i++;
		}
		else if ((j = ft_strichr(&buf[i], ' ')) >= 0)
			n += add(&c, ft_strsub(buf, i, j));
		else
		{
			n += add(&c, ft_strdup(&buf[i]));
			break ;
		}
		i += j;
	}
	return (toarray(e, n));
}
/*
int			main(void)
{
	char	buf[1024];
	char	**arg;
	int		r;

	r = read(0, buf, 1023);
	if (r > 0 && buf[r - 1] == '\n')
		buf[r - 1] = '\0';
	else
		buf[r] = '\0';
	arg = get_arg(buf);
	while (*arg)
	{
		ft_printf("%s\n", *arg++);
	}
}
*/
