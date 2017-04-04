/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:23:05 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/03 22:13:29 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_pathjoin(const char *path, const char *file)
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
	pathfile[i++] = '/';
	while (i < size)
	{
		pathfile[i] = file[l1++];
		i++;
	}
	pathfile[i] = '\0';
	return (pathfile);
}
