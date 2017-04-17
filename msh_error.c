/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 21:51:22 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/16 19:49:02 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_error(int error, const char *msg)
{
	if (error == 0)
		return (0);
	else if (error == MSH_NOT_FOUND)
		ft_fprintf(2, "msh: file not found: %s\n", msg);
	else if (error == MSH_FORK_FAILED)
		ft_fprintf(2, "msh: fork failed\n");
	else if (error == MSH_MALLOC_FAILED)
		ft_fprintf(2, "msh: malloc failed\n");
	else if (error == MSH_NOT_EXECUTABLE)
		ft_fprintf(2, "msh: file not executable: %s\n", msg);
	else if (error == MSH_PROGRAM_NOT_FOUND)
		ft_fprintf(2, "msh: command not found: %s\n", msg);
	else
		ft_fprintf(2, "msh: some error occured\n");
	return (1);
}
