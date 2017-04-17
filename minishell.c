/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:06:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/16 15:59:05 by varnaud          ###   ########.fr       */
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

char	*search_path(const char *cmd, t_msh *msh)
{
	int		i;
	char	*path;

	path = NULL;
	if (!ft_strncmp(cmd, "./", 2))
		return (find_file(".", cmd + 2) ? ft_strdup(cmd) : NULL);
	if (msh->path_list == NULL)
		return (NULL);
	i = 0;
	while (msh->path_list[i])
	{
		if (find_file(msh->path_list[i], cmd))
		{
			path = ft_strcjoin(msh->path_list[i], cmd, '/');
			break ;
		}
		i++;
	}
	return (path);
}

void	free_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->argc)
		free(cmd->argv[i++]);
	i = 0;
	if (cmd->env)
	{
		while (cmd->env[i])
			free(cmd->env[i++]);
		free(cmd->env);
	}
	if (cmd->path)
		free(cmd->path);
	free(cmd->argv);
	free(cmd);
}

void	exec_command(t_msh *msh, t_cmd *cmd, char *path)
{
	if (execve(path, cmd->argv, msh->env) == -1)
	{
		perror("execve");
		print_error(MSH_NOT_EXECUTABLE, path);
	}
	exit(1);
}

static int	exec_program(t_msh *msh, t_cmd *cmd)
{
	char	*path;

	path = search_path(cmd->argv[0], msh);
	if (!path)
		return (print_error(MSH_NOT_FOUND, cmd->argv[0]));
	msh->pid = fork();
	if (msh->pid > 0)
		wait(NULL);
	else if (msh->pid == 0)
		exec_command(msh, cmd, path);
	else
		print_error(MSH_FORK_FAILED, NULL);
	free(path);
	return (0);
}

void	minishell(t_msh *msh)
{
	t_cmd	*cmd;
	int		(*builtin)(t_msh*, t_cmd*);

	while (1)
	{
		ft_printf("%s", msh->prompt);
		msh->line_size = gnl(0, &msh->line);
		if ((cmd = setup_command(msh->line, msh)))
		{
			if ((builtin = find_builtin(msh, cmd)))
				builtin(msh, cmd);
			else
				exec_program(msh, cmd);
		}
		if (msh->line_size > 0)
			free(msh->line);
		free_cmd(cmd);
	}
}
