/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:04:49 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/16 21:14:52 by varnaud          ###   ########.fr       */
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
t_msh			*set_msh(t_msh **msh, int argc, char **argv, char **env);
char			**get_env(char **env, const char *key);
char			*set_prompt(t_msh *msh, const char *prompt);
int				print_error(int error, const char *msg);
void			minishell(t_msh *msh);
//t_cmd			*parse_line(char *line);
t_cmd			*setup_command(char *line, t_msh *msh);
t_command		find_builtin(t_msh *msh, t_cmd *cmd);
char			*search_path(const char *cmd, t_msh *msh);
void			free_cmd(t_cmd *cmd);

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
int				ft_setenv(char ***env, const char *key, const char *value);
int				ft_unsetenv(char ***env, const char *key);
char			**ft_findenv(char **env, const char *key);

#endif
