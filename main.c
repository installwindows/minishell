/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/16 19:44:44 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*set_prompt(t_msh *msh, const char *prompt)
{
	int		len;

	if (prompt == NULL)
		return (NULL);
	len = ft_strlen(prompt);
	if (len >= msh->prompt_bufsize)
	{
		free(msh->prompt);
		msh->prompt_bufsize = len * 2;
		msh->prompt = malloc(sizeof(char) * msh->prompt_bufsize);
	}
	msh->prompt = ft_strcpy(msh->prompt, prompt);
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
