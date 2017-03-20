/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 20:18:06 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/19 20:55:36 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	nbarg(const char *buf)
{
	int		nbwords;
	int		quote;

	nbwords = 0;
	quote = 0;
	while (*buf)
	{
		if (*buf == ' ')
		{
			while (*buf++ == ' ')
				;
			nbwords++;
		}
		else if (*buf == '\\')
			
		else if (*buf == '"' && !quote)
			quote = 1;
		else if (*buf == '"' && quote)
		{
			quote = 0;
			nbwords++;
		}
	}
}

char		**get_arg(const char *buf)
{
	char	**arg;


}
