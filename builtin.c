/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:31:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 21:23:12 by varnaud          ###   ########.fr       */
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
	if (!ft_strcmp(cmd->argv[0], "debug"))
		return (&msh_debug);
	return (msh ? NULL : NULL);
}

int			msh_echo(t_msh *msh, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		ft_printf("%s%s", cmd->argv[i], i < (cmd->argc - 1) ? " " : "");
		i++;
	}
	ft_printf("\n");
	return (!msh);
}

int			msh_cd(t_msh *msh, t_cmd *cmd)
{
	char		cwd[1024];
	char		*dir;
	struct stat	s;

	if (cmd->argc > 1)
		dir = cmd->argv[1];
	else
		dir = msh->home;
	getcwd(cwd, 1024);
	if (stat(dir, &s))
		return (ft_fprintf(2, "cd: No such file or directory: %s\n", dir));
	if (!S_ISDIR(s.st_mode))
		return (ft_fprintf(2, "cd: Not a directory: %s\n", dir));
	if (access(dir, X_OK))
		return (ft_fprintf(2, "cd: Permission denied: %s\n", dir));
	if (chdir(dir) == -1)
		return (ft_fprintf(2, "cd: chdir failed: %s\n", dir));
	ft_setenv(&msh->env, "OLDPWD", cwd);
	ft_setenv(&msh->env, "PWD", dir);
	return (0);
}

int			msh_exit(t_msh *msh, t_cmd *cmd)
{
	int		i;

	if (msh->line)
		free(msh->line);
	if (msh->prompt)
		free(msh->prompt);
	i = 0;
	if (msh->env)
	{
		while (msh->env[i])
			free(msh->env[i++]);
		free(msh->env);
	}
	i = 0;
	if (msh->path_list)
	{
		while (msh->path_list[i])
			free(msh->path_list[i++]);
		free(msh->path_list);
	}
	free (msh);
	free_cmd(cmd);
	gnl(-42, NULL);
	exit(0);
	return (!(msh || cmd));
}

int			msh_debug(t_msh *msh, t_cmd *cmd)
{
	return (!(msh || cmd));
}
