/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:05:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/30 17:43:29 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_argc(char *line)
{
	int		argc;

	argc = 0;
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		if (*line)
			argc++;
		while (*line && *line != ' ')
			line++;
	}
	return (argc);
}

t_cmd		*parse_line(char *line)
{
	t_cmd	*cmd;
	char	*tmp;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	cmd->argc = get_argc(line);
	cmd->argv = malloc(sizeof(char*) * (cmd->argc + 1));
	cmd->argv[cmd->argc] = NULL;
	i = 0;
	tmp = line;
	while (i < cmd->argc)
	{
		while (*line && *line == ' ')
			tmp = ++line;
		while (*line && *line != ' ')
			line++;
		cmd->argv[i++] = ft_strsub(tmp, 0, line - tmp);
	}
	return (cmd);
}

/*
int			main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_cmd *cmd = parse_line(argv[1]);
		int	i = 0;
		while (i < cmd->argc)
		{
			printf("|%s|\n", cmd->argv[i]);
			free(cmd->argv[i++]);
		}
		free(cmd->argv);
		free(cmd);
	}
	else
	{
		parse_line("");
	}
}
*/
