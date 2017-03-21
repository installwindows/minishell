/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 12:22:16 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/19 19:57:51 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "get_next_line.h"
#include "libft.h"
#include "ft_printf.h"
#define BUF_SIZE 255

void	set_command(const char *buf, char ***arg)
{
	*arg = ft_strsplit(buf, ' ');
}

void	unset_command(char ***arg)
{
	size_t	i;

	i = 0;
	while ((*arg)[i])
	{
		free((*arg)[i++]);
	}
	free(*arg);
}

int		main(int argc, char **argv)
{
	char	**arg;
	char	*line;
	int		r;
	pid_t	pid;

	line = NULL;
	while (1)
	{
		ft_printf("$>");
		get_next_line(0, &line);
		set_command(line, &arg);
		if (!arg)
			continue ;
		pid = fork();
		if (pid > 0)
			wait(NULL);
		else if (pid == 0)
		{
			//execve(arg[0], arg, NULL);
			//unset_command(&arg);
			execve(arg[0], argv, NULL);
		}
		if (line)
			free(line);
	}
}
