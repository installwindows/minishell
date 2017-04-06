/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:04:49 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/05 15:52:17 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include "libft.h"

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
	char		*prompt;
	char		**env;
	char		**argv;
	int			argc;
	char		*path;
	char		*home;
	//const struct s_builtin	**builtin;
}				t_msh;
typedef struct	s_builtin
{
	char		*name;
	int 		(*command)(t_msh*, t_cmd*);
}				t_builtin;
typedef int		(*t_command)(t_msh*, t_cmd*);

void			minishell(t_msh *msh);
t_cmd			*parse_line(char *line);
t_command		find_builtin(t_msh *msh, t_cmd *cmd);
char			**get_env(char **env, const char *key);

/*
** Builtin commands
*/

int				msh_echo(t_msh *msh, t_cmd *cmd);
int				msh_cd(t_msh *msh, t_cmd *cmd);
int				msh_setenv(t_msh *msh, t_cmd *cmd);
int				msh_unsetenv(t_msh *msh, t_cmd *cmd);
int				msh_env(t_msh *msh, t_cmd *cmd);
int				msh_exit(t_msh *msh, t_cmd *cmd);
int				msh_printenv(t_msh *msh, t_cmd *cmd);

/*
** TODO Add to libft
*/
char			*ft_strcjoin(const char *path, const char *file, char c);
char			**ft_arrayadd(char **a, const char *env);

#endif
