/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldouble_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 06:07:50 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/22 05:08:50 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

int				int_dexpo(long expo)
{
	int		n;
	int		count;
	int		i;

	n = 0;
	count = 1;
	i = 16;
	while (--i)
	{
		n += (1 & expo) ? count : 0;
		count *= 2;
		expo >>= 1;
	}
	n = n - 16383;
	return (n);
}

char			*int_dmantis(t_80bit d)
{
	char	*n;
	char	*count;
	long	mantis;
	char	*tmp;
	int		mem;

	mantis = d.ldouble.mantis;
	n = ft_strdup("0");
	if ((mem = int_dexpo(d.ldouble.expo)) < 0)
		return (n);
	if ((63 - mem) <= 0)
	{
		count = ft_strpower(2, mem - 63, 10);
		mem = 63;
	}
	else
	{
		mantis >>= (63 - mem);
		count = ft_strdup("1");
	}
	puideux(mem, mantis, &n, &count);
	tmp = n;
	((n = ft_strsum(n, count, 10)) && tmp) ? free(tmp) : 0;
	free(count);
	return (n);
}

static char		*ft_floating(int n, char **count)
{
	char	*i;
	int		len;
	char	*tmp;

	i = ft_strcnew(-n, '0');
	*count = ft_strpower(5, -n, 10);
	tmp = i;
	i = ft_strsum(i, *count, 10);
	free(tmp);
	len = ft_strlen(i);
	tmp = *count;
	*count = ft_strmult(*count, "5", 10);
	free(tmp);
	ft_foisdix(&i, &len);
	return (i);
}

char			*ldouble_mantis(t_80bit d)
{
	char		*n;
	long		mantis;
	char		*count;
	int			i;

	mantis = reverse_bits(d.ldouble.mantis, 63);
	i = int_dexpo(d.ldouble.expo);
	count = NULL;
	if (i < 0 && i != -16383)
		n = ft_floating(i, &count);
	else if (i == -16383)
		return (ft_strdup("0"));
	else
	{
		n = ft_strdup("0");
		count = ft_strdup("5");
	}
	while (i >= 0 && i--)
		mantis >>= 1;
	i = 63 - int_dexpo(d.ldouble.expo);
	puicinq(i, mantis, &n, &count);
	free(count);
	return (n);
}

void			ft_dadjust_width(t_80bit d, t_flags *flags, int **cursor, int i)
{
	while (!flags->la && flags->width-- > ((flags->plus | flags->space)
			& !d.ldouble.signe))
	{
		(flags->zero) ? ft_putchar('0') : ft_putchar(' ');
		(**cursor)++;
	}
	if ((flags->plus || flags->space || d.ldouble.signe) && !i)
		ft_printsignfloat(d.ldouble.signe, flags, cursor);
}
