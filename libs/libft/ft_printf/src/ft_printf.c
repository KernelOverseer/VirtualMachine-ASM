/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:24:34 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/07 18:16:29 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

t_func	call_func(int i)
{
	static const t_func func[] = {
		{'s', O_s, &ft_printstring},
		{'d', O_d, &ft_printnumber},
		{'i', O_i, &ft_printnumber},
		{'u', O_u, &ft_printnumberu},
		{'o', O_o, &ft_printnumberoct},
		{'x', O_x, &ft_printnumberhexmin},
		{'X', O_X, &ft_printnumberhexmaj},
		{'b', O_b, &ft_printnumberbin},
		{'c', O_c, &ft_printchar},
		{'p', O_p, &ft_printadresse},
		{'f', O_f, &ft_printfloat},
		{'t', O_t, &ft_printtime},
		{'k', O_k, &ft_printcolor},
		{'n', O_n, &ft_print_nonprintable},
		{0, O_END, NULL}};

	return (func[i]);
}

int		print_cnv(const char *string, va_list arg, int *cursor, t_flags flags)
{
	int		i;
	t_func	new;

	i = -1;
	while (1)
	{
		new = call_func(++i);
		if (*string == new.cnv_type)
		{
			(*(new.f))(arg, cursor, flags);
			return (1);
		}
		else if (new.cnv == O_END)
			return (0);
	}
}

char	detect_cnv_exist(const char *string)
{
	int		i;
	t_func	new;

	i = -1;
	while (1)
	{
		new = call_func(++i);
		if (*string == new.cnv_type)
			return (new.cnv_type);
		else if (new.cnv == O_END)
			return (0);
	}
}

int		ft_printf(const char *string, ...)
{
	va_list	ap;
	t_flags flags;
	int		cursor;
	char	*s;

	va_start(ap, string);
	s = (char *)string;
	cursor = 0;
	ft_initflags(&flags);
	while (*s)
	{
		if (*s != '%')
		{
			ft_putchar(*s);
			cursor++;
		}
		else if (!detect_cnv_exist(s))
			s = detect_flg(++s, ap, &cursor, &flags);
		else
			print_cnv(s, ap, &cursor, flags);
		s++;
	}
	return (cursor);
}
