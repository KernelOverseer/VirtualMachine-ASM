/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@1337.MA>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 18:19:02 by abiri             #+#    #+#             */
/*   Updated: 2020/02/03 10:16:48 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_atou(const char *str)
{
	long long	number;
	int			i;

	i = 0;
	number = 0;
	if ((str[0] >= 9 && str[0] <= 13) || str[0] == ' ')
		return (ft_atou(++str));
	if (str[0] == '-' && str[1] >= '0' && str[1] <= '9')
	{
		number = ft_atou(++str);
		return (number * -1);
	}
	if (str[0] == '+' && str[1] >= '0' && str[1] <= '9')
		number = ft_atou(++str);
	else if (str[0] != '-')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			number = (number * 10) + (str[i] - '0');
			++i;
		}
	}
	return ((unsigned int)number);
}
