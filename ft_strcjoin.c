/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 15:24:04 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/05 15:52:10 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strcjoin(const char *path, const char *file, char c)
{
	char	*pathfile;
	int		i;
	int		l1;
	int		l2;
	int		size;

	l1 = ft_strlen(path);
	l2 = ft_strlen(file);
	size = l1 + l2 + 1;
	pathfile = malloc(sizeof(char) * size + 1);
	i = 0;
	while (i < l1)
	{
		pathfile[i] = path[i];
		i++;
	}
	l1 = 0;
	pathfile[i++] = c;
	while (i < size)
	{
		pathfile[i] = file[l1++];
		i++;
	}
	pathfile[i] = '\0';
	return (pathfile);
}

char	**ft_arrayadd(char **a, const char *env)
{
	char	**new;
	int		size;
	int		i;

	size = 0;
	while (a[size])
		size++;
	new = malloc(sizeof(char*) * (size + 1));
	i = 0;
	while (i < size)
	{
		new[i] = a[i];
		i++;
	}
	new[i++] = ft_strdup(env);
	new[i] = NULL;
	return (new);
}