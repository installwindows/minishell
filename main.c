/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/05 15:29:51 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_env(char **env, const char *key)
{
	int		len;

	len = ft_strlen(key);
	while (*env)
	{
		if (!ft_strncmp(*env, key, len))
			return (env);
		env++;
	}
	return (NULL);
}

int			main(int argc, char **argv, char **env)
{
	//const char	*builtin[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit"};
	//const t_builtin	builtin[] = {
	//	{"echo", &msh_echo}, {"cd", &msh_cd}, {"setenv", &msh_setenv},
	//	{"unsetenv", &msh_unsetenv}, {"env", &msh_env}, {"exit", &msh_exit}
	//};
	t_msh		*msh;

	msh = malloc(sizeof(t_msh));
	ft_memset(msh, 0, sizeof(t_msh));
	//msh->builtin = &builtin;
	msh->argv = argv;
	msh->argc = argc;
	msh->env = env;
	msh->prompt = malloc(sizeof(char) * 1024);
	ft_strcpy(msh->prompt, "\e[92m$>\e[39m");
	msh->pid = 42;
	msh->path = *get_env(env, "PATH") + 5;
	msh->home = *get_env(env, "HOME") + 5;
	minishell(msh);
}
