/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:31:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/01 14:55:10 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_builtin(t_msh *msh, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (msh->builtin[i])
		if (!ft_strcmp(msh->builtin[i++], cmd->argv[0]))
		{
			
			return (0);
		}
	return (1);
}

int		echo(t_msh *msh)
{

	return (0);
}
