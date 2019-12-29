/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldouble.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 05:36:56 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/22 02:23:38 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static void		ft_round(char **f, t_flags *flags, int **cursor, t_80bit d)
{
	char	*tmp;
	int		last_digit;
	int		i;

	i = 0;
	if ((flags->plus || flags->space || d.ldouble .signe) &&
			!flags->la && (flags->width < 0 || flags->zero))
	{
		ft_printsignfloat(d.ldouble .signe, flags, cursor);
		i = 1;
	}
	last_digit = ft_strlen(*f) - 1;
	if ((*f)[last_digit] >= '5')
	{
		(*f)[last_digit] = '\0';
		tmp = *f;
		*f = ft_strsum(*f, "1", 10);
		tmp ? free(tmp) : 0;
		(flags->precision > 0) && flags->width--;
	}
	ft_dadjust_width(d, flags, cursor, i);
}

static int		get_float(t_80bit d, char **f, char **intt)
{
	char	*mant;
	char	*fmantis;
	size_t	len;

	mant = int_dmantis(d);
	*intt = ft_strsum(mant, "1", 10);
	len = ft_strlen(mant);
	fmantis = ldouble_mantis(d);
	*f = ft_strjoin(mant, fmantis);
	fmantis ? free(fmantis) : 0;
	mant ? free(mant) : 0;
	return (len);
}

static int		ft_print_point(char **f, t_flags flags,
				int *precision, size_t len)
{
	int		cursor;
	char	*tmp;

	cursor = 0;
	tmp = *f;
	while ((**f && --(*precision) >= 0))
	{
		if (!len--)
		{
			ft_putchar('.');
			cursor++;
		}
		ft_putchar(*(*f)++);
		if (flags.hash && flags.precision == 0 && !len)
		{
			ft_putchar('.');
			cursor++;
		}
	}
	tmp ? free(tmp) : 0;
	return (cursor);
}

static int		ft_len_intt(char *intt, char *f, size_t *len)
{
	int	i;

	i = 0;
	while (intt[i] == f[i])
		i++;
	if (i != 0 && *len < ft_strlen(intt))
		*len = ft_strlen(intt);
	free(intt);
	return (*len);
}

void			ft_printldouble(va_list arg, int *cursor, t_flags flags)
{
	t_80bit		ld;
	char		*f;
	char		*intt;
	int			precision;
	size_t		len;

	ld.ld = va_arg(arg, long double);
	if (ft_dinfini(ld, &f, &flags, &cursor))
	{
		len = get_float(ld, &f, &intt);
		precision = (flags.precision != -1) ? flags.precision : 6;
		flags.width -= precision + len + 1;
		flags.la ? flags.zero = 0 : 0;
		(ld.ldouble.signe && (ld.ldouble.signe = 1)) ? flags.width-- : 0;
		f = ft_strfreesub(&f, 0, precision + len + 1, 1);
		ft_round(&f, &flags, &cursor, ld);
		precision += ft_len_intt(intt, f, &len);
		*cursor += precision + ft_print_point(&f, flags, &precision, len);
		while (precision > 0 && precision--)
			ft_putchar('0');
		while (flags.la && flags.width-- >
				((flags.plus | flags.space) & !ld.ldouble.signe) && (*cursor)++)
			flags.zero ? ft_putchar('0') : ft_putchar(' ');
	}
}
