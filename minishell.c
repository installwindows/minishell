/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:06:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/30 18:10:29 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(const char *cmd, t_msh *msh)
{
	char	**dirs;
	char	*path;

	dirs = strsplit(msh->path, ':');
	
	return (path);
}

int		exec_command(t_msh *msh)
{
	t_cmd	**cmd;
	char	*path;

	cmd = parse_line(msh->line);
	path = find_path(cmd[0], msh);
	return (0);
}

void	minishell(t_msh *msh)
{
	while (1)
	{
		ft_printf("%d-%s", msh->pid, msh->psone);
		msh->size = gnl(0, &msh->line);
		msh->pid = fork();
		if (msh->pid > 0)
		{
			wait(NULL);
		}
		else if (msh->pid == 0)
		{
			exit(exec_command(msh));
		}
		else
			ft_fprintf(2, "Fork failed\n");
		if (msh->size > 0)
			free(msh->line);
	}
}
