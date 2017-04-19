/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:11:51 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 22:08:05 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_file(const char *path, const char *file)
{
	DIR				*p;
	struct dirent	*e;
	int				found;

	found = 0;
	if (!(p = opendir(path)))
		return (0);
	while ((e = readdir(p)))
		if (e->d_name[0] == '.')
			continue ;
		else if (!ft_strcmp(e->d_name, file))
		{
			found = 1;
			break ;
		}
	closedir(p);
	return (found);
}

char		*search_path(const char *cmd, t_msh *msh)
{
	int			i;
	char		*path;
	struct stat	s;

	path = NULL;
	if (ft_strchr(cmd, '/'))
		return (!stat(cmd, &s) ? ft_strdup(cmd) : NULL);
	if (msh->path_list == NULL)
		return (NULL);
	i = 0;
	while (msh->path_list[i])
	{
		if (find_file(msh->path_list[i], cmd))
		{
			path = ft_strcjoin(msh->path_list[i], cmd, '/');
			break ;
		}
		i++;
	}
	return (path);
}

t_cmd		*free_cmd(t_cmd *cmd)
{
	int		i;

	if (cmd == NULL)
		return (NULL);
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	i = 0;
	if (cmd->env)
	{
		while (cmd->env[i])
			free(cmd->env[i++]);
		free(cmd->env);
	}
	if (cmd->path)
		free(cmd->path);
	free(cmd);
	return (NULL);
}
