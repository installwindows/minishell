/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/15 21:43:35 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**get_env(char **env, const char *key)
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
