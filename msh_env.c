/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 15:23:48 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/07 21:18:38 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		free_cmd(c);
		return (NULL);
	}
	return (c);
}

int		msh_env(t_msh *msh, t_cmd *cmd)
{
	t_cmd	*p;

	if (cmd->argc < 2)
		return (ft_fprintf(2, "usage: env [key=value]... [program [arg]...]\n"));
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
