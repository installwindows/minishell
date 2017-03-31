/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:04:49 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/30 17:46:46 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "gnl.h"
# include "libft.h"
# include "ft_printf.h"

typedef struct	s_cmd
{
	char		**argv;
	int			argc;
}				t_cmd;

typedef struct	s_msh
{
	char		*line;
	int			size;
	pid_t		pid;
	char		*psone;
	char		**env;
	char		**argv;
	int			argc;
	char		*path;
}				t_msh;

void	minishell(t_msh *msh);
t_cmd	*parse_line(char *line);

#endif
