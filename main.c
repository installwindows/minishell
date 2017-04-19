/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/18 22:25:04 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*set_prompt(t_msh *msh, int status)
{
	char	cwd[1024];

	getcwd(cwd, 1017);
	if (msh->home)
		ft_strsubs(cwd, msh->home, "~");
	ft_strcpy(msh->prompt, "\e[1m\e[35m");
	ft_strcat(msh->prompt, cwd);
	if (status)
		ft_strcat(msh->prompt, "\e[91m$\e[0m\e[39m");
	else
		ft_strcat(msh->prompt, "\e[32m$\e[0m\e[39m");
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
	signal(SIGINT, int_handler);
	minishell(msh);
}
