/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/30 17:52:43 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_path(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			return (*env + 5);
		env++;
	}
	return (NULL);
}

int			main(int argc, char **argv, char **env)
{
	t_msh	*msh;

	msh = malloc(sizeof(t_msh));
	ft_memset(msh, 0, sizeof(t_msh));
	msh->argv = argv;
	msh->argc = argc;
	msh->env = env;
	msh->psone = ft_strdup("$>");
	msh->pid = 42;
	msh->path = set_path(env);
	minishell(msh);
}
