/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 20:28:05 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/26 02:42:12 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	ft_assigntypechar(va_list arg, uintmax_t *number, t_flags flags)
{
	if (flags.lflag == 1)
		*number = va_arg(arg, uintmax_t);
	else if (flags.lflag == 0)
		*number = va_arg(arg, unsigned int);
}

void	ft_printstring(va_list arg, int *cursor, t_flags flags)
{
	char	*s;
	char	null[7];
	int		precision;
	int		size;

	ft_strcpy(null, "(null)");
	s = va_arg(arg, char *);
	if (s == NULL)
		s = null;
	size = (int)ft_strlen(s);
	precision = (flags.precision < size)
	&& flags.precision != -1 ? flags.precision : size;
	*cursor += flags.width > precision ? flags.width : precision;
	if (size)
		flags.width -= precision;
	if (flags.la)
		flags.zero = 0;
	while ((!flags.la || !(*s)) && --flags.width >= 0)
		flags.zero == 1 ? ft_putchar('0') : ft_putchar(' ');
	while (--precision >= 0 && *s)
		ft_putchar(*s++);
	while (--flags.width >= 0 && flags.la)
		flags.zero == 1 ? ft_putchar('0') : ft_putchar(' ');
}

void	ft_printchar(va_list arg, int *cursor, t_flags flags)
{
	uintmax_t c;

	ft_assigntypechar(arg, &c, flags);
	*cursor += flags.width ? flags.width : 1;
	if (flags.la)
		flags.zero = 0;
	while (--flags.width >= 1 && !flags.la)
		flags.zero == 1 ? ft_putchar('0') : ft_putchar(' ');
	ft_putchar(c);
	while (--flags.width >= 0 && flags.la)
		flags.zero == 1 ? ft_putchar('0') : ft_putchar(' ');
}

void	ft_printpercent(int *cursor, t_flags flags)
{
	*cursor += flags.width ? flags.width : 1;
	if (flags.la)
		flags.zero = 0;
	while (--flags.width >= 1 && !flags.la)
		flags.zero == 1 ? ft_putchar('0') : ft_putchar(' ');
	ft_putchar('%');
	while (--flags.width >= 0 && flags.la)
		flags.zero == 1 ? ft_putchar('0') : ft_putchar(' ');
}

void	ft_hashprint(int **cursor, unsigned char type, t_flags flags)
{
	if (type == 'x')
		ft_putstr("0x");
	else if (type == 'X')
		ft_putstr("0X");
	if (flags.width || flags.la)
		(**cursor) += 2;
}
