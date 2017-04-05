/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubesc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 21:26:57 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/04 16:21:00 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
