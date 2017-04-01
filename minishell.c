/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:06:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/31 19:29:24 by varnaud          ###   ########.fr       */
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
	int		i;

	if (!ft_strncmp(cmd, "./", 2))
		return (find_file(".", cmd + 2) ? ft_strdup(cmd) : NULL);
	path = NULL;
	path_list = ft_strsplit(msh->path, ':');
	if (path_list == NULL)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		if (find_file(path_list[i], cmd))
		{
			path = ft_pathjoin(path_list[i], cmd);
			break ;
		}
		free(path_list[i++]);
	}
	while (path_list[i])
		free(path_list[i++]);
	free(path_list);
	return (path);
}

void	free_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->argc)
		free(cmd->argv[i++]);
	free(cmd->argv);
	free(cmd);
}

int		exec_command(t_msh *msh)
{
	t_cmd	*cmd;
	char	*path;
	int		r;

	r = 0;
	cmd = parse_line(msh->line);
	if (cmd->argv[0])
	{
		path = find_path(cmd->argv[0], msh);
		if (path)
		{
			//ft_printf("Command found! %s\n", path);
			if (execve(path, cmd->argv, msh->env) == -1)
				ft_fprintf(2, "Can't execute command: %s\n", path);
			free(path);
			r = 1;
		}
		else
			ft_fprintf((r = 2), "msh: command not found: %s\n", cmd->argv[0]);
	}
	free_cmd(cmd);
	return (r);
}

void	minishell(t_msh *msh)
{
	//msh->line = "";
	//exec_command(msh);
	while (1)
	{
		ft_printf("%s", msh->psone);
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
