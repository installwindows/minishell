/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_msh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 21:39:27 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/16 23:57:42 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**set_mshenv(t_msh *msh, char **env)
{
	int		i;
	int		size;

	if (env == NULL)
		return (NULL);
	i = 0;
	size = 0;
	while (env[i])
	{
		size++;
		i++;
	}
	if (!(msh->env = malloc(sizeof(char*) * (size + 1))))
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

static char		**set_msh_path(t_msh *msh)
{
	int		i;
	char	**path;

	if (msh->path_list)
	{
		i = 0;
		while (msh->path_list[i])
			free(msh->path_list[i++]);
		free(msh->path_list);
	}
	msh->path_list = NULL;
	path = ft_findenv(msh->env, "PATH");
	if (path)
		msh->path_list = ft_strsplit(*path + 5, ':');
	return (msh->path_list);
}

t_msh			*set_msh(t_msh **msh, int argc, char **argv, char **env)
{
	char	**home;

	if (!(*msh = malloc(sizeof(t_msh))))
		return (NULL);
	ft_memset(*msh, 0, sizeof(t_msh));
	(*msh)->opt.argv = argv;
	(*msh)->opt.argc = argc;
	if (env != NULL)
		if (!((*msh)->env = set_mshenv(*msh, env)))
			return (NULL);
	(*msh)->prompt_bufsize = 1024;
	if (!((*msh)->prompt = malloc(sizeof(char) * 1024)))
		return (NULL);
	set_prompt(*msh, "\e[92m$>\e[39m");
	(*msh)->pid = 42;
	home = ft_findenv(env, "HOME");
	if (home)
		(*msh)->home = *home + 5;
	set_msh_path(*msh);
	return (*msh);
}
