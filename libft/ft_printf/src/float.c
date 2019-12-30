/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 05:36:56 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/24 05:46:34 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static void		ft_round(char **f, t_flags *fl, int **cursor, t_64bit d)
{
	char	*tmp;
	int		last_digit;
	int		i;

	i = 0;
	if ((fl->plus || fl->space || d.dfloat.signe) &&
			!fl->la && (fl->width < 0 || fl->zero))
	{
		ft_printsignfloat(d.dfloat.signe, fl, cursor);
		i = 1;
	}
	last_digit = ft_strlen(*f) - 1;
	if ((*f)[last_digit] >= '5')
	{
		(*f)[last_digit] = '\0';
		tmp = *f;
		*f = ft_strsum(*f, "1", 10);
		tmp ? free(tmp) : 0;
		(fl->precision > 0) && fl->width--;
	}
	ft_adjust_width(d, fl, cursor, i);
}

static int		get_float(t_64bit d, char **f, char **intt)
{
	char	*mant;
	char	*fmantis;
	size_t	len;

	mant = int_mantis(d);
	*intt = ft_strsum(mant, "1", 10);
	len = ft_strlen(mant);
	fmantis = float_mantis(d);
	*f = ft_strjoin(mant, fmantis);
	free(mant);
	free(fmantis);
	return (len);
}

static int		ft_print_point(char **f, t_flags fl,
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
		if (fl.hash && fl.precision == 0 && !len)
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

void			ft_printfloat(va_list arg, int *cursor, t_flags fl)
{
	t_64bit		d;
	char		*f;
	char		*intt;
	int			precision;
	size_t		len;

	if (fl.lflag == 2)
		return (ft_printldouble(arg, cursor, fl));
	d.d = (double)va_arg(arg, double);
	if (!ft_infini(d, &f, &fl, &cursor))
		return ;
	len = get_float(d, &f, &intt);
	precision = (fl.precision != -1) ? fl.precision : 6;
	fl.width -= precision + len + 1;
	fl.la ? fl.zero = 0 : 0;
	(d.dfloat.signe && (d.dfloat.signe = 1)) ? fl.width-- : 0;
	f = ft_strfreesub(&f, 0, precision + len + 1, 1);
	ft_round(&f, &fl, &cursor, d);
	precision += ft_len_intt(intt, f, &len);
	*cursor += precision + ft_print_point(&f, fl, &precision, len);
	while (precision > 0 && precision--)
		ft_putchar('0');
	while (fl.la && fl.width-- > ((fl.plus | fl.space) & !d.dfloat.signe)
	&& (*cursor)++)
		fl.zero ? ft_putchar('0') : ft_putchar(' ');
}
