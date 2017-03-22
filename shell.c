/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 12:22:16 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 16:38:20 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "get_next_line.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_arg.c"
#define BUF_SIZE 255

void	set_command(const char *buf, char ***arg)
{
	*arg = get_arg(buf);
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
	*arg = NULL;
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
		r = read(0, buf, BUF_SIZE);
		if (r < 0)
			continue ;
		else if (r > 0 && buf[r - 1] == '\n')
			buf[r - 1] = '\0';
		else
			buf[r] = '\0';
		set_command(buf, &arg);
		if (!arg)
			continue ;
		pid = fork();
		if (pid < 0)
			ft_printf("Can't fork");
		if (pid > 0)
			wait(NULL);
		else if (pid == 0)
		{
			if (execve(arg[0], arg, NULL) == -1)
				ft_printf("Can't exec %s\n", arg[0]);
			unset_command(&arg);
			//execve("/bin/ls", argv, NULL);
		}
		if (line)
			free(line);
	}
}
