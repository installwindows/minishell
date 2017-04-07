/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:31:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/06 17:40:55 by varnaud          ###   ########.fr       */
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
	//if (!ft_strcmp(cmd->argv[0], "env"))
	//	return (&msh_env);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (&msh_exit);
	if (!ft_strcmp(cmd->argv[0], "printenv"))
		return (&msh_printenv);
	if (!ft_strcmp(cmd->argv[0], "debug"))
		return (&msh_debug);
	return (NULL);
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
	int		r;

	r = 0;
	if (cmd->argc > 1)
	{
		if (chdir(cmd->argv[1]) == -1)
			ft_fprintf((r = 2), "Can't cd into: %s\n", cmd->argv[1]);
	}
	else
	{
		if (chdir(msh->home) == -1)
			ft_fprintf((r = 2), "Can't cd into: %s\n", msh->home);
	}
	return (r);
}

int		msh_setenv(t_msh *msh, t_cmd *cmd)
{
	char	**key;
	char	*new;
	char	**env;

	if (cmd->argc <= 2)
		return (ft_fprintf(2, "usage: setenv key value\n"));
	key = get_env(msh->env, cmd->argv[1]);
	if (key)
	{
		new = ft_strcjoin(cmd->argv[1], cmd->argv[2], '=');
		free(*key);
		*key = new;
	}
	else
	{
		env = ft_arrayadd(msh->env, (new = ft_strcjoin(cmd->argv[1], cmd->argv[2], '=')));
		free(new);
		free(msh->env);
		msh->env = env;
	}
	return (0);
}

int		msh_unsetenv(t_msh *msh, t_cmd *cmd)
{
	char	**env;
	char	**key;

	if (cmd->argc < 2)
		return (ft_fprintf(2, "usage: unsetenv [key]\n"));
	key = get_env(msh->env, cmd->argv[1]);
	if (key)
	{
		env = ft_arrayrm(msh->env, *key);
		free(*key);
		free(msh->env);
		msh->env = env;
	}
	return (0);
}

static t_cmd	*set_builtin_env(t_msh *msh, t_cmd *cmd)
{
	char	**env;
	t_cmd	*c;

	if (cmd->argc < 2)
		return (NULL);
	env = 
	env = malloc(sizeof(t_cmd));

}

int		msh_env(t_msh *msh, t_cmd *cmd)
{
	char	*path;
	char	**env;
	char	**argv;
	t_cmd	*p;

	p = set_builtin_env(msh, cmd);
	if (cmd->argc < 2)
		return (ft_fprintf(2, "usage: env [key=value]... [program [arg]...]\n"));
	path = find_path(cmd->argv[cmd->argc - 1], msh);
	if (!path)
		return (print_error(MSH_PROGRAM_NOT_FOUND, cmd->argv[cmd->argc - 1]));
	msh->pid = fork();
	if (msh->pid > 0)
		wait(NULL);
	else if (msh->pid == 0)
	{
		env = get_key_value(t_cmd->argv);
		if (execve(path, argv, env) == -1)
			print_error(MSH_NOT_EXECUTABLE, path);
		exit(1);
	}
	else
		print_error(MSH_FORK_FAILED, NULL);
	free(path);
	return (0);
}

int		msh_exit(t_msh *msh, t_cmd *cmd)
{
	exit(0);
	return (0);
}

int		msh_printenv(t_msh *msh, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (msh->env[++i])
	{
		if (cmd->argc > 1)
			if (ft_strncmp(msh->env[i], cmd->argv[1], ft_strlen(cmd->argv[1])))
				continue ;
		ft_printf("%s\n", msh->env[i]);
	}
	return (0);
}

int		msh_debug(t_msh *msh, t_cmd *cmd)
{
	return (0);
}
