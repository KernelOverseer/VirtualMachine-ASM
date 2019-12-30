/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parsing_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:25:41 by abiri             #+#    #+#             */
/*   Updated: 2019/12/30 18:36:42 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_match_charset_times(char *string, char *charset, int min, int max)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (!ft_ischarin(charset, string[index]))
			break;
		index++;
	}
	if (index < min || index > max)
		return (-1);
	return (index);
}

int	ft_parse_int(char *number, int *integer)
{
	int	index;
	int	count;

	index = 0;
	if ((count = ft_match_charset_times(&number[index], "+-", 0, 1)) < 0)
		return (0);
	index += count;
	if ((count = ft_match_charset_times(&number[index], "0123456789", 1, 10)) < 0)
		return (0);
	index += count;
	if (number[index] != '\0')
		return (0);
	*integer = ft_atoi(number);
	return (1);
}
