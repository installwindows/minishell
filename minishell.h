/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:04:49 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/06 15:11:48 by varnaud          ###   ########.fr       */
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
# include "msh_error.h"

typedef struct	s_cmd
{
	char		*path;
	char		**argv;
	char		**env;
	int			argc;
}				t_cmd;

typedef struct	s_mshopt
{
	int			flags;
	char		**argv;
	int			argc;
}				t_mshopt;

typedef struct	s_msh
{
	char		*line;
	int			line_size;
	pid_t		pid;
	char		*prompt;
	char		**env;
	char		*path;
	char		*home;
	t_mshopt	opt;
}				t_msh;

typedef int		(*t_command)(t_msh*, t_cmd*);

int				print_error(int error, const char *msg);
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
int				msh_debug(t_msh *msh, t_cmd *cmd);

/*
** TODO Add to libft
*/
char			*ft_strcjoin(const char *path, const char *file, char c);
char			**ft_arrayadd(char **a, const char *env);
char			**ft_arrayrm(char **a, const char *key);

#endif
