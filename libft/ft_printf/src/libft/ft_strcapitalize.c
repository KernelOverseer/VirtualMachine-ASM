/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 02:11:39 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/20 23:15:00 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int i;
	int notcapitalized;

	i = 0;
	notcapitalized = 1;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z' && notcapitalized == 1)
		{
			str[i] = str[i] - 32;
			notcapitalized = 0;
		}
		else if ((str[i] >= 'A' && str[i] <= 'Z') && notcapitalized == 0)
		{
			str[i] = str[i] + 32;
		}
		else if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '+' || str[i] == '-')
			notcapitalized = 1;
		else
			notcapitalized = 0;
		i++;
	}
	return (str);
}
