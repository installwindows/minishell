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
	char	buf[BUF_SIZE + 1];
	char	**arg;
	int		r;
	pid_t	pid;
/*
	for (int j = 0; argv[j]; j++)
		ft_printf("%d: %s\n", j, argv[j]);
	r = read(0, buf, BUF_SIZE);
	set_command(buf, &arg);
	ft_printf("command: %s\n", arg[0]);
	for (int i = 1; arg[i]; i++)
	{
		ft_printf("%d: %s\n", i, arg[i]);
		free(arg[i]);
	}
	free(arg);
	exit(0);
*/
	while (1)
	{
		ft_printf("$>");
		r = read(0, buf, BUF_SIZE);
		if (r < 0)
			continue ;
		buf[r] = '\0';
		set_command(buf, &arg);
		if (!arg)
			continue ;
		pid = fork();
		if (pid > 0)
			wait(NULL);
		else if (pid == 0)
		{
			//execve(arg[0], arg, NULL);
			//unset_command(&arg);
			execve("/bin/ls", argv, NULL);
		}
	}
}
