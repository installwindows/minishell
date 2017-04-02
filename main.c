/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/01 22:13:56 by varnaud          ###   ########.fr       */
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
	//const char	*builtin[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit"};
	const t_builtin	builtin[] = {
		{"echo", &msh_echo}, {"cd", &msh_cd}, {"setenv", &msh_setenv},
		{"unsetenv", &msh_unsetenv}, {"env", &msh_env}, {"exit", &msh_exit}
	};
	t_msh		*msh;

	msh = malloc(sizeof(t_msh));
	ft_memset(msh, 0, sizeof(t_msh));
	msh->builtin = &builtin;
	msh->argv = argv;
	msh->argc = argc;
	msh->env = env;
	msh->prompt = ft_strdup("$>");
	msh->pid = 42;
	msh->path = set_path(env);
	minishell(msh);
}
