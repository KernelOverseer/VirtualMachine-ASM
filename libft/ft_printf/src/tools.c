/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:31:32 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/08 01:19:03 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int					ft_numbersize(unsigned long long number)
{
	int i;

	i = 1;
	while (number /= 10)
		i++;
	return (i);
}

void				ft_putunbr(unsigned long long nbr)
{
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + '0');
	}
	else
		ft_putchar(nbr + '0');
}

long long int		ft_assigntype(va_list arg, t_flags flags)
{
	t_type d;

	d.lli = (long long int)va_arg(arg, long long int);
	if (flags.lflag == 1)
		return (d.li);
	else if (flags.lflag > 1)
		return (d.lli);
	else if (flags.hflag == 1)
		return (d.si);
	else if (flags.hflag == 2)
		return (d.sc);
	return (d.i);
}

long unsigned int	ft_assigntypeunsigned(va_list arg, t_flags flags)
{
	t_typeunisgned d;

	d.u = (unsigned long int)va_arg(arg, unsigned long int);
	if (flags.lflag > 0)
		return (d.u);
	else if (flags.hflag == 2)
		return (d.c);
	else if (flags.hflag == 1)
		return (d.s);
	return (d.d);
}

void				ft_printsign(long long number, t_flags flags)
{
	if (number < 0)
		ft_putchar('-');
	else if (flags.plus)
		ft_putchar('+');
	else if (flags.space)
		ft_putchar(' ');
}
