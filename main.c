/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/05 21:21:40 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**get_env(char **env, const char *key)
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

static char		**set_mshenv(t_msh *msh, char **env)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (env[i])
	{
		size++;
		i++;
	}
	if (!(msh->env = malloc(sizeof(char*) * size)))
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!(msh->env[i] = ft_strdup(env[i])))
			return (NULL);
		i++;
	}
	msh->env[i] = NULL;
	return (msh->env);
}

static t_msh	*set_msh(t_msh **msh, int argc, char **argv, char **env)
{
	char	*path;
	char	*home;

	if (!(*msh = malloc(sizeof(t_msh))))
		return (NULL);
	ft_memset(*msh, 0, sizeof(t_msh));
	(*msh)->opt.argv = argv;
	(*msh)->opt.argc = argc;
	if (env != NULL)
		if (!((*msh)->env = set_mshenv(*msh, env)))
			return (NULL);
	if (!((*msh)->prompt = malloc(sizeof(char) * 1024)))
		return (NULL);
	ft_strcpy((*msh)->prompt, "\e[92m$>\e[39m");
	(*msh)->pid = 42;
	path = *get_env(env, "PATH");
	if (path)
		(*msh)->path = path + 5;
	home = *get_env(env, "HOME");
	if (home)
		(*msh)->home = home + 5;
	return (*msh);
}

int				main(int argc, char **argv, char **env)
{
	t_msh		*msh;

	msh = set_msh(&msh, argc, argv, env);
	if (msh == NULL)
	{
		ft_fprintf(2, "Can't start: %s\n", argv[0]);
		exit(1);
	}
	minishell(msh);
}
