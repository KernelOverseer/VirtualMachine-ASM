/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:25:41 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/17 22:42:19 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int number;
	int n;

	n = 0;
	number = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
	*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		n = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ((*str >= '0' && *str <= '9') && *str != '\0')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	if (n == 1)
		return (-number);
	return (number);
}
