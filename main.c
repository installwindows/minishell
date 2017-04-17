/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/17 14:32:05 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*set_prompt(t_msh *msh, const char *prompt)
{
	int		len;
	int		i;

	if (prompt == NULL)
	{
		ft_strcpy(msh->prompt, "\e[92m$\e[39m");
		return (NULL);
	}
	len = ft_strlen(prompt) + ft_strlen("\e[92m$\e[39m");
	if (len >= msh->prompt_bufsize)
	{
		free(msh->prompt);
		msh->prompt_bufsize = len * 2;
		msh->prompt = malloc(sizeof(char) * msh->prompt_bufsize);
	}
	ft_strcpy(msh->prompt, "\e[92m");
	if (ft_strcmp(prompt, msh->home))
	{
		ft_strcpy(msh->prompt + 5, prompt);
		ft_strcpy(msh->prompt + 5 + ft_strlen(prompt), "$\e[39m");
	}
	else
		ft_strcpy(msh->prompt + 5, "~$\e[39m");
	return (msh->prompt);
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
