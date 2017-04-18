/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:04:49 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/17 21:07:32 by varnaud          ###   ########.fr       */
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

/*
** malloc,free
** access
** open, close, read, write
** opendir, readdir, closedir
** getcwd, chdir
** stat, lstat, fstat
** fork, execve
** wait, waitpid, wait3, wait4
** signal, kill
** exit
*/

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
	int			prompt_bufsize;
	char		**env;
	char		**path_list;
	char		*home;
	t_mshopt	opt;
}				t_msh;

typedef int		(*t_command)(t_msh*, t_cmd*);

void			minishell(t_msh *msh);
int				print_error(int error, const char *msg);

/*
** Command exec
*/

void			free_cmd(t_cmd *cmd);
t_cmd			*setup_command(char *line, t_msh *msh);
t_command		find_builtin(t_msh *msh, t_cmd *cmd);
char			*search_path(const char *cmd, t_msh *msh);

/*
** msh set
*/

t_msh			*set_msh(t_msh **msh, int argc, char **argv, char **env);
char			*set_prompt(t_msh *msh, int status);
char			**set_msh_path(t_msh *msh);

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

#endif
