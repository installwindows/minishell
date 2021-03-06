/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:09:29 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/12 17:21:14 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <inttypes.h>
#include "libft.h"
#include "ft_printf.h"

int		x_conversion(t_flags *flags, va_list *args)
{
	unsigned long long	d;

	if (flags->f & F_PRECISION && flags->precision >= 0)
		flags->f &= ~F_ZERO;
	if (flags->f & F_HH)
		d = (unsigned char)va_arg(*args, unsigned int);
	else if (flags->f & F_H)
		d = (unsigned short int)va_arg(*args, unsigned int);
	else if (flags->f & F_L)
		d = va_arg(*args, unsigned long int);
	else if (flags->f & F_LL)
		d = va_arg(*args, unsigned long long int);
	else if (flags->f & F_J)
		d = va_arg(*args, uintmax_t);
	else if (flags->f & F_Z)
		d = va_arg(*args, size_t);
	else
		d = va_arg(*args, unsigned int);
	return (handle_unsigned_number(d, 16, flags));
}
