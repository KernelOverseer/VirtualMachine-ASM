/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 00:36:25 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/09 02:45:44 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void		ft_printnumberoct(va_list arg, int *cursor, t_flags fl)
{
	unsigned long long	d;
	int					precision;
	int					size;
	int					width;

	d = ft_assigntypeunsigned(arg, fl);
	size = (int)ft_strlen(ft_itoa_base(d, 8, 0));
	width = fl.width;
	precision = ft_getvalueo(&fl, &cursor, size, d);
	while (fl.width-- > (fl.space) && !fl.la)
		(fl.zero && fl.precision == -1) ?
		ft_putchar('0') : ft_putchar(' ');
	while (precision-- > size)
		ft_putchar('0');
	if (!fl.precision && !width && fl.hash && d == 0)
		ft_putchar('0');
	if (!fl.precision && d == 0 && width)
		(fl.hash) ? ft_putchar('0') : ft_putchar(' ');
	else if (fl.precision || width || d)
		ft_putstr(ft_itoa_base(d, 8, 0));
	while (fl.width-- >= 0 && fl.la)
		fl.zero ? ft_putchar('0') : ft_putchar(' ');
}

void		ft_printnumberhexmin(va_list arg, int *cursor, t_flags fl)
{
	unsigned long long	d;
	int					precision;
	int					size;
	int					width;

	d = ft_assigntypeunsigned(arg, fl);
	size = (int)ft_strlen(ft_itoa_base(d, 16, 0));
	width = fl.width;
	precision = ft_getvaluex(&fl, &cursor, size, d);
	while (!fl.la && !(fl.zero && fl.precision == -1) && fl.width-- > fl.space)
		ft_putchar(' ');
	if (fl.hash && d)
		ft_hashprint(&cursor, 'x', fl);
	while (!fl.la && fl.width-- > 0)
		(fl.zero && fl.precision == -1) ?
		ft_putchar('0') : ft_putchar(' ');
	while (precision-- > size)
		ft_putchar('0');
	if (!fl.precision && d == 0 && width)
		ft_putchar(' ');
	else if (fl.precision || width || d)
		ft_putstr(ft_itoa_base(d, 16, 0));
	while (fl.width-- > 0 && fl.la)
		fl.zero ? ft_putchar(' ') : ft_putchar(' ');
}

void		ft_printnumberbin(va_list arg, int *cursor, t_flags fl)
{
	unsigned short int d;

	d = va_arg(arg, int);
	ft_putstr(ft_itoa_base(d, 2, 0));
	(*cursor)++;
	fl.zero = 0;
}

void		ft_printnumberhexmaj(va_list arg, int *cursor, t_flags fl)
{
	unsigned long long	d;
	int					precision;
	int					size;
	int					width;

	d = ft_assigntypeunsigned(arg, fl);
	size = (int)ft_strlen(ft_itoa_base(d, 16, 1));
	width = fl.width;
	precision = ft_getvaluex(&fl, &cursor, size, d);
	while (!fl.la && !(fl.zero && fl.precision == -1) && fl.width-- > fl.space)
		ft_putchar(' ');
	if (fl.hash && d)
		ft_hashprint(&cursor, 'X', fl);
	while (!fl.la && fl.width-- > 0)
		(fl.zero && fl.precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	while (precision-- > size)
		ft_putchar('0');
	if (!fl.precision && d == 0 && width)
		ft_putchar(' ');
	else if (fl.precision || width || d)
		ft_putstr(ft_itoa_base(d, 16, 1));
	while (fl.width-- > 0 && fl.la)
		fl.zero ? ft_putchar(' ') : ft_putchar(' ');
}

void		ft_printadresse(va_list arg, int *cursor, t_flags fl)
{
	unsigned long	ud;
	int				precision;
	int				size;

	ud = (unsigned long)va_arg(arg, void *);
	size = (int)ft_strlen(ft_itoa_base(ud, 16, 0));
	precision = ft_getvaluead(&fl, &cursor, size);
	(fl.width < -1) && ((*cursor) += 2);
	ft_putstr("0x");
	while (precision-- > size)
		ft_putchar('0');
	if (fl.precision == 0 && ud == 0)
	{
		if ((fl.width == -1 && !fl.space && !fl.plus))
			ft_putchar(' ');
		else if (fl.hash)
			ft_putchar('0');
		else if (!precision)
			(*cursor)--;
	}
	else
		ft_putstr(ft_itoa_base(ud, 16, 0));
	while (fl.width-- >= 0 && fl.la)
		fl.zero ? ft_putchar('0') : ft_putchar(' ');
}
