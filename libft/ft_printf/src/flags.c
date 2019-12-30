/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:50:22 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/16 01:30:43 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void		ft_initflags(t_flags *flags)
{
	flags->sign = -1;
	flags->la = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->hash = 0;
	flags->length = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->zero = 0;
	flags->hflag = 0;
	flags->lflag = 0;
}

char		*detect_flg(char *string, va_list arg, int *cursor, t_flags *flags)
{
	while (*string)
	{
		if (!ft_assignflag(flags, &string) &&
		!ft_assignflag2(arg, flags, &string))
		{
			if (detect_cnv_exist(string) != 0 || *string == '%')
				(*string == '%') ? ft_printpercent(cursor, *flags)
					: print_cnv(string, arg, cursor, *flags);
			else if (*string == 'D' || *string == 'U' || *string == 'O')
			{
				flags->lflag = 1;
				if (*string == 'D')
					print_cnv("d", arg, cursor, *flags);
				else if (*string == 'U')
					print_cnv("u", arg, cursor, *flags);
				else
					print_cnv("o", arg, cursor, *flags);
			}
			ft_initflags(flags);
			return (string);
		}
		string++;
	}
	return (string);
}

int			ft_assignflag(t_flags *flags, char **string)
{
	if (**string == '#')
		flags->hash = 1;
	else if (**string == '0')
		flags->zero = 1;
	else if (**string == ' ')
		flags->space = 1;
	else if (**string == '+')
		flags->plus = 1;
	else if (**string == '-')
		flags->la = 1;
	else if (**string == 'l' || **string == 'z' || **string == 'j')
		flags->lflag += 1;
	else if (**string == 'h')
		flags->hflag += 1;
	else if (**string == 'L')
		flags->lflag = 2;
	else
		return (0);
	return (1);
}

int			ft_assignflag2(va_list arg, t_flags *flags, char **str)
{
	int		star;

	if ((ft_atoi(*str) != 0 && flags->width == 0) || (**str == '0'))
	{
		flags->width = ft_atoi(*str);
		(*str) += (ft_numbersize(ft_atoi(*str))) - 1;
	}
	else if (**str == '.' && (*str)++)
	{
		(star = (**str == '*') ? va_arg(arg, int) : ft_atoi(*str));
		(flags->precision = ABS(star));
		if ((**str == '*') || (**str == '0') || ft_atoi(*str) != 0)
			(*str) += (**str == '*') ? 0 : (ft_numbersize(star)) - 1;
		else
			(*str)--;
	}
	else if (**str == '*')
	{
		star = va_arg(arg, int);
		(flags->la = (star < 0) ? 1 : flags->la);
		(flags->width = ABS(star));
	}
	else
		return (0);
	return (1);
}
