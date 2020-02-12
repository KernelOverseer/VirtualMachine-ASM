/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 18:19:02 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 11:24:24 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	long_verif(unsigned long long int a, int sign)
{
	if (sign == -1 && (a - 1) > 9223372036854775807)
		return (0);
	if (sign == 1 && a > 9223372036854775807)
		return (-1);
	return ((int)(a * sign));
}

int			ft_atoi(const char *str)
{
	int						i;
	unsigned long long int	a;
	int						sign;

	i = 0;
	a = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] > 47 && str[i] < 58)
			a = (a * 10) + (str[i] - 48);
		else
			break ;
		i++;
	}
	return (long_verif(a, sign));
}