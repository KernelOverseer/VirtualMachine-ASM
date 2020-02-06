/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parsing_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:25:41 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:12:27 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int				ft_match_charset_times(char *string, char *charset,
	int min, int max)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (!ft_ischarin(charset, string[index]))
			break ;
		index++;
	}
	if (index < min || index > max)
		return (-1);
	return (index);
}

int				ft_int_endian(int i)
{
	return (((i >> 24) & 0xFF) | ((i >> 8) & 0xFF00) |
		((i << 8) & 0xFF0000) | ((i << 24) & 0xFF000000));
}

short			ft_short_endian(short i)
{
	return ((i >> 8 | i << 8) & 0xFFFF);
}

unsigned int	ft_switch_endian(unsigned int value)
{
	return (((value & 0x000000ff) << 24) | ((value & 0x0000ff00) << 8) |
		((value & 0x00ff0000) >> 8) | ((value & 0xff000000) >> 24));
}

int				ft_parse_int(char *number, int *integer)
{
	int	index;
	int	count;

	index = 0;
	if ((count = ft_match_charset_times(&number[index], "+-", 0, 1)) < 0)
		return (0);
	index += count;
	if ((count = ft_match_charset_times(&number[index],
		"0123456789", 1, 10)) < 0)
		return (0);
	index += count;
	if (number[index] != '\0')
		return (0);
	*integer = ft_atoi(number);
	return (1);
}
