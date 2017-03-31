/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:06:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/31 14:57:07 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_file(const char *path, const char *file)
{
	DIR				*p;
	struct dirent	*e;
	int				found;

	found = 0;
	if (!(p = opendir(path)))
		return (0);
	while ((e = readdir(p)))
		if (!ft_strcmp(e->d_name, file))
		{
			found = 1;
			break ;
		}
	closedir(p);
	return (found);
}

char	*find_path(const char *cmd, t_msh *msh)
{
	char	**path_list;
	char	*path;

	path = NULL;
	path_list = ft_strsplit(msh->path, ':');
	if (path_list == NULL)
		return (NULL);
	while (*path_list)
	{
		if (find_file(*path_list, cmd))
		{
			path = ft_pathjoin(*path_list, cmd);
			break ;
		}
		free(*path_list++);
	}
	while (*path_list)
		free(*path_list++);
	free(path_list);
	return (path);
}

int		exec_command(t_msh *msh)
{
	t_cmd	*cmd;
	char	*path;

	cmd = parse_line(msh->line);
	path = find_path(cmd->argv[0], msh);
	if (path)
	{
		ft_printf("Command found! %s\n", path);
		free(path);
	}
	else
		ft_fprintf(2, "msh: command not found: %s\n", cmd);
	return (0);
}

void	minishell(t_msh *msh)
{
	msh->line = "ls";
	exec_command(msh);
	while (0)
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
