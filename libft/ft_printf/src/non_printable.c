/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_printable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 05:36:56 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/25 14:14:19 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int				ft_print_bs(void)
{
	ft_putchar('\\');
	return (1);
}

static void		ft_equivalent(char a, int **cursor)
{
	if (a == 7 && ft_print_bs() && *(*cursor)++)
		ft_putchar('a');
	else if (a == 8 && ft_print_bs() && *(*cursor)++)
		ft_putchar('b');
	else if (a == 9 && ft_print_bs() && *(*cursor)++)
		ft_putchar('t');
	else if (a == 10 && ft_print_bs() && *(*cursor)++)
		ft_putchar('n');
	else if (a == 11 && ft_print_bs() && *(*cursor)++)
		ft_putchar('v');
	else if (a == 12 && ft_print_bs() && *(*cursor)++)
		ft_putchar('f');
	else if (a == 13 && ft_print_bs() && *(*cursor)++)
		ft_putchar('r');
	else if (a == 27 && ft_print_bs() && *(*cursor)++)
		ft_putchar('e');
	else
		ft_putchar(a);
}

void			ft_print_nonprintable(va_list arg, int *cursor, t_flags flags)
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
		ft_equivalent(*s++, &cursor);
	while (--flags.width >= 0 && flags.la)
		flags.zero == 1 ? ft_putchar('0') : ft_putchar(' ');
}
