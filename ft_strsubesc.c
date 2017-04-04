/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubesc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 21:26:57 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/03 23:50:09 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*fresh;
	size_t	i;

	fresh = ft_strnew(len);
	if (fresh == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (s[start] == '\\' && s[start + 1]  && s[start + 1] != '\\')
			start += 2;
		fresh[i] = s[start];
		i++;
		start++;
	}
	return (fresh);
}
