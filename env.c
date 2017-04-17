/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:11:39 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/16 21:26:18 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_freeenv(char ***env)
{
	int		i;

	i = 0;
	if (env == NULL || *env == NULL)
		return ;
	while((*env)[i])
		free((*env)[i++]);
	free(*env);
	*env = NULL;;
}

char	**ft_findenv(char **env, const char *key)
{
	int		len;

	if (env == NULL || key == NULL)
		return (NULL);
	len = ft_strlen(key);
	while (*env)
	{
		if (!ft_strncmp(*env, key, len))
			return (env);
		env++;
	}
	return (NULL);
}

int		ft_setenv(char ***env, const char *key, const char *value)
{
	char	**variable;
	char	*newvalue;
	char	**newenv;

	if (key == NULL || value == NULL)
		return (1);
	variable = ft_findenv(*env, key);
	newvalue = ft_strcjoin(key, value, '=');
	if (variable)
	{
		free(*variable);
		*variable = newvalue;
	}
	else
	{
		newenv = ft_arrayadd(*env, newvalue);
		free(*env);
		*env = newenv;
	}
	return (0);
}

int		ft_unsetenv(char ***env, const char *key)
{
	char	**variable;
	char	**newenv;

	if (env == NULL || key == NULL)
		return (1);
	variable = ft_findenv(*env, key);
	if (variable)
	{
		newenv = ft_arrayrm(*env, *variable);
		free(*variable);
		free(*env);
		*env = newenv;
	}
	else
		return (1);
	return (0);
}
