/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:07:37 by mfetoui           #+#    #+#             */
/*   Updated: 2019/01/16 01:12:13 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strccut(char *str, char *s1, int option)
{
	int		i;
	char	*s;
	int		len;

	len = ft_strlen(str);
	s = (char *)malloc(sizeof(char ) * len);
	i = 0;
	if (option == 1)
		i = ft_strccut_loop(i, str, s1, s);
	else if (option == 0)
		while (len > 0)
		{
			if (str[len] == s1[1] && str[len - 1] == s1[0])
			{
				len--;
				break ;
			}
			len--;
		}
	while (str[len] != '\0')
		s[i++] = str[len++];
	s[i] = '\0';
	return (s);
}

int		ft_strccut_loop(int i, char *str, char *s1, char *s)
{
	while (str[i] != '\0')
	{
		if (str[i] == s1[0] && str[i + 1] == s1[1])
			break ;
		s[i] = str[i];
		i++;
	}
	return (i);
}
