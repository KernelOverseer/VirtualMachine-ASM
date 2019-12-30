/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 06:07:50 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/20 13:27:24 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void		puideux(int mem, long mantis, char **n, char **count)
{
	char	*tmp;

	while (mem--)
	{
		if (1 & mantis)
		{
			tmp = *n;
			*n = ft_strsum(*n, *count, 10);
			free(tmp);
		}
		tmp = *count;
		*count = ft_strmult(*count, "2", 10);
		free(tmp);
		mantis >>= 1;
	}
}

void		puicinq(int i, long mantis, char **n, char **count)
{
	int		len;
	char	*tmp;

	while (i >= 0 && i--)
	{
		len = ft_strlen(*n);
		if (1 & mantis)
		{
			tmp = *n;
			*n = ft_strsum(*n, *count, 10);
			free(tmp);
		}
		ft_foisdix(n, &len);
		tmp = *count;
		*count = ft_strmult(*count, "5", 10);
		free(tmp);
		mantis >>= 1;
	}
}

void		ft_printsignfloat(long sign, t_flags *flags, int **cursor)
{
	(**cursor)++;
	if (sign)
		ft_putchar('-');
	else if (flags->plus)
		ft_putchar('+');
	else if (flags->space)
		ft_putchar(' ');
}

void		ft_print_nan_inf(t_64bit d, t_flags *flags, char **f)
{
	if (d.dfloat.mantis)
		*f = ft_strdup("nan");
	else if (!d.dfloat.mantis && d.dfloat.signe)
		*f = ft_strdup("-inf");
	else if (!d.dfloat.mantis && !d.dfloat.signe)
	{
		if (flags->plus)
			*f = ft_strdup("+inf");
		else if (flags->space)
			*f = ft_strdup(" inf");
		else
			*f = ft_strdup("inf");
	}
}

int			ft_infini(t_64bit d, char **f, t_flags *flags, int **cursor)
{
	int		precision;
	int		size;
	int		expo;

	expo = int_expo(d.dfloat.expo);
	if (expo == 1024)
	{
		ft_print_nan_inf(d, flags, f);
		size = (int)ft_strlen(*f);
		precision = size;
		**cursor += flags->width > precision ? flags->width : precision;
		flags->width -= size ? precision : 0;
		flags->la ? flags->zero = 0 : 0;
		while ((!flags->la || !(**f)) && --flags->width >= 0)
			ft_putchar(' ');
		ft_putstr(*f);
		free(*f);
		while (--flags->width >= 0 && flags->la)
			ft_putchar(' ');
		return (0);
	}
	return (1);
}
