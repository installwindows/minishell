/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:31:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/02 19:33:45 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	find_builtin(t_msh *msh, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (&msh_echo);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (&msh_cd);
	if (!ft_strcmp(cmd->argv[0], "setenv"))
		return (&msh_setenv);
	if (!ft_strcmp(cmd->argv[0], "unsetenv"))
		return (&msh_unsetenv);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (&msh_env);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (&msh_exit);
	return (NULL);
	/*
	int		i;

	i = 0;
	while (msh->builtin[i])
	{
		if (!ft_strcmp(msh->builtin[i]->name, cmd->argv[0]))
		{
			return (msh->builtin[i]->command);
		}
		i++;
	}
	return (NULL);
	*/
}

int		msh_echo(t_msh *msh, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		ft_printf("%s%s", cmd->argv[i], i < (cmd->argc - 1) ? " " : "");
		i++;
	}
	ft_printf("\n");
	return (0);
}

int		msh_cd(t_msh *msh, t_cmd *cmd)
{
	ft_printf("cd\n");
	return (0);
}

int		msh_setenv(t_msh *msh, t_cmd *cmd)
{
	ft_printf("setenv\n");
	return (0);
}

int		msh_unsetenv(t_msh *msh, t_cmd *cmd)
{
	ft_printf("unsetenv\n");
	return (0);
}

int		msh_env(t_msh *msh, t_cmd *cmd)
{
	ft_printf("env\n");
	return (0);
}

int		msh_exit(t_msh *msh, t_cmd *cmd)
{
	exit(0);
	return (0);
}
