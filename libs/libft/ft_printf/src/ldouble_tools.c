/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldouble_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 06:07:50 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/22 05:17:20 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void		ft_dprint_nan_inf(t_80bit d, t_flags *flags, char **f)
{
	if (d.ldouble.mantis)
		*f = ft_strdup("NAN");
	else if (!d.ldouble.mantis && d.ldouble.signe)
		*f = ft_strdup("-INF");
	else if (!d.ldouble.mantis && !d.ldouble.signe)
	{
		if (flags->plus)
			*f = ft_strdup("+INF");
		else if (flags->space)
			*f = ft_strdup(" INF");
		else
			*f = ft_strdup("INF");
	}
}

int			ft_dinfini(t_80bit ld, char **f, t_flags *flags, int **cursor)
{
	int		precision;
	int		size;
	int		expo;

	expo = int_expo(ld.ldouble.expo);
	if (expo == 16384)
	{
		ft_dprint_nan_inf(ld, flags, f);
		size = (int)ft_strlen(*f);
		precision = size;
		**cursor += flags->width > precision ? flags->width : precision;
		flags->width -= size ? precision : 0;
		flags->la ? flags->zero = 0 : 0;
		while ((!flags->la || !(**f)) && --flags->width >= 0)
			ft_putchar(' ');
		ft_putstr(*f);
		while (--flags->width >= 0 && flags->la)
			ft_putchar(' ');
		return (0);
	}
	return (1);
}
