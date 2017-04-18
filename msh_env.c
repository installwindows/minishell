/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 15:23:48 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 15:20:36 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			msh_setenv(t_msh *msh, t_cmd *cmd)
{
	char	**key;
	char	*new;
	char	**env;
	int		r;

	if (cmd->argc != 3 || cmd->argv[1][0] == '\0')
		return (ft_fprintf(2, "usage: setenv [key] [value]\n"));
	r = ft_setenv(&msh->env, cmd->argv[1], cmd->argv[2]);
	if (!r && !ft_strcmp(cmd->argv[1], "PATH"))
		set_msh_path(msh);
	if (r)
		ft_fprintf(2, "setenv: Cannot set key: %s\n", cmd->argv[1]);
	return (r);
}

int			msh_unsetenv(t_msh *msh, t_cmd *cmd)
{
	char	**env;
	char	**key;
	int		r;

	if (cmd->argc != 2 || cmd->argv[1][0] == '\0')
		return (ft_fprintf(2, "usage: unsetenv [key]\n"));
	r = ft_unsetenv(&msh->env, cmd->argv[1]);
	if (!r && !ft_strcmp(cmd->argv[1], "PATH"))
		set_msh_path(msh);
	if (r)
		ft_fprintf(2, "unsetenv: Key not found: %s\n", cmd->argv[1]);
	return (r);
}

int			msh_printenv(t_msh *msh, t_cmd *cmd)
{
	int		i;

	if (msh->env == NULL)
		return (0);
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

static t_cmd	*set_builtin_env(t_msh *msh, t_cmd *cmd)
{
	t_cmd	*c;
	int		i;
	int		j;
	int		k;

	c = malloc(sizeof(t_cmd));
	c->argv = malloc(sizeof(char*) * cmd->argc);
	c->env = malloc(sizeof(char*) * cmd->argc);
	i = 0;
	j = 0;
	k = 0;
	while (cmd->argv[++i])
	{
		while (ft_strchr(cmd->argv[i], '='))
			c->env[j++] = ft_strdup(cmd->argv[i++]);
		if (cmd->argv[i])
			c->argv[k++] = ft_strdup(cmd->argv[i]);
	}
	c->env[j] = NULL;
	c->argv[k] = NULL;
	c->path = search_path(c->argv[0], msh);
	if (!c->argv || !c->path)
		return (free_cmd(c));
	return (c);
}

int		msh_env(t_msh *msh, t_cmd *cmd)
{
	t_cmd	*p;

	if (cmd->argc == 1)
		return (msh_printenv(msh, cmd));
	if (cmd->argc < 2)
		return (ft_fprintf(2,
				"usage: env [key=value]... [program [arg]...]\n"));
	if (!(p = set_builtin_env(msh, cmd)))
		return (1);
	msh->pid = fork();
	if (msh->pid > 0)
		wait(NULL);
	else if (msh->pid == 0)
	{
		if (execve(p->path, p->argv, p->env) == -1)
			print_error(MSH_NOT_EXECUTABLE, p->path);
		exit(1);
	}
	else
		print_error(MSH_FORK_FAILED, NULL);
	free_cmd(p);
	return (0);
}
