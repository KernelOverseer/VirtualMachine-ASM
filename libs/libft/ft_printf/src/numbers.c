/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:50:29 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/08 18:08:48 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void			ft_printnumber(va_list arg, int *cursor, t_flags fl)
{
	long long	d;
	int			precision;

	d = ft_assigntype(arg, fl);
	fl.sign = d < 0 ? 1 : 0;
	precision = 0;
	ft_getvaluesd(&fl, &precision, &cursor, d);
	while (fl.width-- > (fl.sign | fl.plus | fl.space) && !fl.la)
		(fl.zero && fl.precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	if ((fl.plus || fl.space || d < 0) && (!fl.zero ||
	fl.precision != -1 || ((fl.plus || fl.zero) && !fl.precision)))
		ft_printsign(d, fl);
	while (precision-- > ft_numbersize(ABS(d)))
		ft_putchar('0');
	if (fl.precision == 0 && d == 0)
	{
		if ((fl.width == -1 && !fl.space && !fl.plus))
			ft_putchar(' ');
		else if (!precision)
			(*cursor)--;
	}
	else
		ft_putunbr(ABS(d));
	while (fl.width-- >= (fl.sign | fl.plus | fl.space) && fl.la)
		fl.zero ? ft_putchar('0') : ft_putchar(' ');
}

void			ft_printnumberu(va_list arg, int *cursor, t_flags flags)
{
	long unsigned int	d;
	int					precision;
	int					width;

	d = ft_assigntypeunsigned(arg, flags);
	width = flags.width;
	precision = 0;
	ft_getvaluesu(&flags, &precision, &cursor, d);
	while (!flags.la && flags.width-- > (flags.plus | flags.space))
		(flags.zero && flags.precision == -1) ? ft_putchar('0')
		: ft_putchar(' ');
	while (precision-- > ft_numbersize(d))
		ft_putchar('0');
	if (!flags.precision && d == 0 && width)
		ft_putchar(' ');
	else if (flags.precision || width || d)
		ft_putunbr(d);
	while (flags.width-- > 0 && flags.la)
		flags.zero ? ft_putchar('0') : ft_putchar(' ');
}

void			ft_getvaluesu(t_flags *flags, int *precision, int **cursor,
long unsigned int d)
{
	if (flags->precision || d != 0)
		*precision = flags->precision > ft_numbersize(d)
			? flags->precision : ft_numbersize(d);
	**cursor += flags->width > *precision ? flags->width : *precision;
	*precision = flags->precision > ft_numbersize(d)
		? flags->precision : ft_numbersize(d);
	flags->width -= *precision;
	flags->zero = (flags->la || flags->width < 0
			|| *precision > ft_numbersize(d)) ? 0 : flags->zero;
}

void			ft_getvaluesd(t_flags *flags, int *precision, int **cursor,
long long d)
{
	int			width;

	width = flags->width;
	if (!((flags->plus || flags->la || flags->space) &&
	flags->width && !flags->precision && d == 0))
		*precision = flags->precision > ft_numbersize(ABS(d))
			? flags->precision : ft_numbersize(ABS(d));
	**cursor += flags->width > *precision ? flags->width :
		*precision + (flags->sign | flags->plus | flags->space);
	flags->width -= *precision;
	flags->zero = (flags->la || flags->width < 0
			|| *precision > ft_numbersize(ABS(d))) ? 0 : flags->zero;
	if ((flags->zero && flags->precision) || (flags->zero && width))
		if ((flags->precision == -1 && !flags->space) ||
		((flags->plus || flags->space) && flags->precision == -1))
			ft_printsign(d, *flags);
}
