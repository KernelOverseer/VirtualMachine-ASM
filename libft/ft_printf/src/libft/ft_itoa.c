/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:01:31 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/20 23:34:19 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strrevsign(int n, char *str)
{
	char	temp;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[counter] != '\0')
		counter++;
	if (n == 1)
		str[counter] = '-';
	else
		counter--;
	while (counter > i)
	{
		temp = str[i];
		str[i] = str[counter];
		str[counter] = temp;
		counter--;
		i++;
	}
	return (str);
}

static	char	*ft_putnbritoa(int n, char *result)
{
	unsigned int	nb;

	nb = n;
	if (nb >= 10)
	{
		ft_putnbritoa(nb / 10, result + 1);
		ft_putnbritoa(nb % 10, result);
	}
	else
		*result = nb + '0';
	return (result);
}

char			*ft_itoa(int n)
{
	int		negative;
	char	*result;
	int		nbr;
	int		size;

	nbr = n;
	size = 1;
	while (nbr /= 10)
		size++;
	negative = 0;
	if (n < 0)
	{
		n = n * -1;
		negative = 1;
	}
	if ((result = (char*)malloc(sizeof(char) * ((size + negative) + 1))))
	{
		ft_bzero(result, ((size + negative) + 1));
		result = ft_putnbritoa(n, result);
		return (ft_strrevsign(negative, result));
	}
	return (NULL);
}
