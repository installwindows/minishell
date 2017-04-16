/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:05:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/15 23:03:59 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strsubesc(char const *s, unsigned int start, size_t len)
{
	char	*fresh;
	size_t	i;

	fresh = ft_strnew(len);
	if (fresh == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		if (s[start] == '\\' && s[start + 1]  && s[start + 1] != '\\')
		{
			len--;
			start += 1;
		}
		fresh[i] = s[start];
		i++;
		start++;
	}
	return (fresh);
}

static int	get_argc(char *line)
{
	int		i;
	int		argc;
	int		q;

	i = 0;
	argc = 0;
	q = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
			argc++;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] == '"' && line[i > 0 ? i - 1 : i] != '\\')
				while (line[++i] && line[i] != '"')
					;
			i++;
		}
	}
	return (argc);
}

t_cmd		*parse_line(char *line)
{
	t_cmd	*cmd;
	char	*tmp;
	char	*b;
	int		i;
	int		q;

	b = line;
	cmd = malloc(sizeof(t_cmd));
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->argc = get_argc(line);
	cmd->argv = malloc(sizeof(char*) * (cmd->argc + 1));
	cmd->argv[cmd->argc] = NULL;
	i = 0;
	tmp = line;
	q = 0;
	while (i < cmd->argc)
	{
		while (*line && *line == ' ')
			tmp = ++line;
		q = 0;
		while (*line)
		{
			if (!q && *line == ' ')
				break ;
			if (q && *line == '"' && *(line - 1 >= b ? line - 1 : line) != '\\')
				break ;
			if (!q && *line == '"' && *(line - 1 >= b ? line - 1 : line) != '\\')
			{
				tmp = line + 1;
				q = 1;
			}
			line++;
		}
		cmd->argv[i++] = ft_strsubesc(tmp, 0, line - tmp);
		if (q)
			line++;
	}
	return (cmd);
}

#define IS_WHITE(c) (c == ' ' || c == '\t' || c == '\v' || c == '\r')
#define P_V(line, i) (i > 0 ? line[i - 1] : line[i])
static int	setup_line(char *line, int i, int count)
{
	while (line[i] && IS_WHITE(line[i]))
		line[i++] = '\0';
	if (line[i])
	{
		count++;
		while (line[i] && !IS_WHITE(line[i]))
		{
			if (line[i] == '"' && P_V(line, i) != '\\')
				while (line[++i])
					if (line[i] == '"' && P_V(line, i) != '\\')
						break ;
			i++;
		}
	}
	else
		return (count);
	return (setup_line(line, i, count));
}

static char	**split_line(char *line, int size, int count, char c)
{
	char	**argv;
	int		i;
	int		j;
	int		k;
	int		l;

	if (!(argv = malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	argv[count] = NULL;
	i = 0;
	j = 0;
	while (count--)
	{
		while (i < size && line[i] == c)
			i++;
		k = i;
		while (i < size && line[i] != c)
			i++;
		if (!(argv[j] = malloc(sizeof(char) * (i - k + 1))))
			return (NULL);
		l = 0;
		while ((argv[j][l] = line[k++]))
			l += line[k - 1] == '"' && P_V(line, k - 1) != '\\' ? 0 : 1;
		j++;
	}
	return (argv);
}

t_cmd		*setup_command(char *line)
{
	t_cmd	*cmd;
	char	**argv;
	int		argc;
	int		len;

	len = ft_strlen(line);
	argc = setup_line(line, 0, 0);
	if (argc == 0)
		return (NULL);
	argv = split_line(line, len, argc, '\0');
	if (argv == NULL)
		return (NULL);
	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->argv = argv;
	cmd->argc = argc;
	cmd->path = NULL;
	cmd->env = NULL;
	return (cmd);
}

/*
int			main(int argc, char **argv)
{
	t_cmd	*cmd;
	int		i;
	int		r;
	char	*line;

	//printf("argc: %d\n", argc - 1);
	//while (*++argv)
	//	ft_printf("%s\n", *argv);
	//ft_printf("----\n");
	r = gnl(0, &line);
	if (r == -1 || !line)
	{
		ft_fprintf(2, "%s: no input\n", argv[0]);
		return (1);
	}
	cmd = setup_command(line);
	if (cmd == NULL)
		return (ft_fprintf(2, "No command to set\n"));
	ft_printf("path: %s\nargc: %d\n", cmd->path, cmd->argc);
	i = 0;
	while (i < cmd->argc)
	{
		ft_printf("|%s|\n", cmd->argv[i]);
		free(cmd->argv[i++]);
	}
	free(cmd->argv);
	free(cmd);
	free(line);
}
*/
