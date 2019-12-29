/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:13:25 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/09 02:50:19 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int			ft_getvaluex(t_flags *fl, int **cursor, int size
		, long unsigned int d)
{
	int precision;

	precision = 0;
	if (fl->precision || d != 0)
		precision = fl->precision > size ? fl->precision : size;
	fl->width = (fl->hash && d) ? fl->width - 2 : fl->width;
	**cursor += fl->width > precision ? fl->width : precision;
	precision = fl->precision > size ? fl->precision : size;
	fl->width -= precision;
	fl->zero = (fl->la || fl->width < 0 || precision > (size + 1))
		? 0 : fl->zero;
	return (precision);
}

int			ft_getvalueo(t_flags *fl, int **cursor, int size
		, long unsigned int d)
{
	int precision;

	precision = fl->precision > size ? fl->precision : size;
	if (fl->precision <= size && fl->hash == 1 && d)
		precision++;
	else if (!fl->precision && !fl->width && !fl->hash && d == 0)
		precision = 0;
	**cursor += fl->width > precision ? fl->width : precision;
	fl->width -= precision;
	fl->zero = (fl->la || fl->width < 0 || precision > (size + 1))
		? 0 : fl->zero;
	return (precision);
}

int			ft_getvaluead(t_flags *fl, int **cursor, int size)
{
	int precision;

	precision = fl->precision > size ? fl->precision : size;
	**cursor += fl->width > precision ? fl->width : precision;
	fl->width -= precision + 2;
	fl->zero = (fl->la || fl->width < 0 || precision > (size + 1))
		? 0 : fl->zero;
	while (fl->width-- > (fl->plus | fl->space) && !fl->la && !fl->hash)
		(fl->zero && fl->precision == -1) ? ft_putchar('0') : ft_putchar(' ');
	return (precision);
}

long		reverse_bits(long b, int bit_len)
{
	long	r;

	r = 0;
	while (bit_len--)
	{
		r = (r << 1) | (b & 1);
		b >>= 1;
	}
	return (r);
}

void		ft_foisdix(char **str, int *len)
{
	char	*fois_dix;
	int		i;

	(*len)++;
	fois_dix = (char*)malloc(sizeof(char) * (*len + 1));
	fois_dix[*len] = '\0';
	i = -1;
	while ((*str)[++i] != '\0')
		fois_dix[i] = (*str)[i];
	fois_dix[i] = '0';
	free(*str);
	*str = fois_dix;
}
