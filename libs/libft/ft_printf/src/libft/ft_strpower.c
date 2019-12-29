/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:29:25 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/07 08:29:26 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MAX 100000

static int	multiply(int x, int *res, int res_size, int base)
{
	int		carry;
	int		prod;
	int		i;

	i = 0;
	carry = 0;
	while (i < res_size)
	{
		prod = res[i] * x + carry;
		res[i] = prod % base;
		carry = prod / base;
		i++;
	}
	while (carry)
	{
		res[res_size] = carry % base;
		carry = carry / base;
		res_size++;
	}
	return (res_size);
}

static void	put_into_s(char **s, int *res, int res_size)
{
	int		i;
	int		j;

	j = 0;
	i = res_size - 1;
	while (i >= 0)
	{
		(*s)[j] = (res[i] < 10) ? res[i] + '0' : res[i] + 'a' - 10;
		i--;
		j++;
	}
}

char		*ft_strpower(int x, int n, int base)
{
	char	*s;
	int		res[MAX];
	int		res_size;
	int		temp;
	int		i;

	if (n == 0)
		return (ft_strdup("1"));
	res_size = 0;
	temp = x;
	while (temp)
	{
		res[res_size++] = temp % base;
		temp = temp / base;
	}
	i = 2;
	while (i++ <= n)
		res_size = multiply(x, res, res_size, base);
	s = ft_strnew(res_size);
	put_into_s(&s, res, res_size);
	return (s);
}
