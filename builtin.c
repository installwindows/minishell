/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:31:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/01 22:14:50 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	find_builtin(t_msh *msh, t_cmd *cmd)
{
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
}

int		msh_echo(t_msh *msh, t_cmd *cmd)
{
	ft_printf("echo\n");
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
	ft_printf("exit\n");
	return (0);
}
