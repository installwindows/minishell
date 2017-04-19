/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:06:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 22:40:37 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_msh *msh, t_cmd *cmd, char *path)
{
	if (execve(path, cmd->argv, msh->env) == -1)
	{
		print_error(MSH_NOT_EXECUTABLE, path);
	}
	exit(1);
}

static int	exec_program(t_msh *msh, t_cmd *cmd)
{
	char	*path;
	int		stat_loc;

	stat_loc = 0;
	path = search_path(cmd->argv[0], msh);
	if (!path)
		return (print_error(MSH_NOT_FOUND, cmd->argv[0]));
	msh->pid = fork();
	if (msh->pid > 0)
		wait(&stat_loc);
	else if (msh->pid == 0)
		exec_command(msh, cmd, path);
	else
		print_error(MSH_FORK_FAILED, NULL);
	free(path);
	return (stat_loc);
}

void	minishell(t_msh *msh)
{
	t_cmd	*cmd;
	int		(*builtin)(t_msh*, t_cmd*);
	int		status;

	status = 0;
	while (1)
	{
		cmd = NULL;
		msh->line = NULL;
		ft_printf("%s", set_prompt(msh, status));
		msh->line_size = gnl(0, &msh->line);
		if (msh->line_size == 0)
			msh_exit(msh, cmd);
		if ((cmd = setup_command(msh->line, msh)))
		{
			if ((builtin = find_builtin(msh, cmd)))
				status = builtin(msh, cmd);
			else
				status = exec_program(msh, cmd);
		}
		if (msh->line_size > 0)
			free(msh->line);
		free_cmd(cmd);
	}
}
