/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 21:51:22 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/05 22:17:56 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_error(int error, const char *msg)
{
	if (error == 0)
		return (0);
	else if (error == MSH_NOT_FOUND)
		ft_fprintf(2, "File not found: %s\n", msg);
	else if (error == MSH_FORK_FAILED)
		ft_fprintf(2, "Fork failed\n");
	else if (error == MSH_MALLOC_FAILED)
		ft_fprintf(2, "Malloc failed\n");
	else if (error == MSH_NOT_EXECUTABLE)
		ft_fprintf(2, "File not executable: %s\n", msg);
	else
		ft_fprintf(2, "Some error occured\n");
	return (1);
}
