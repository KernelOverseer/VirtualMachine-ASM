/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 19:59:09 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/11 23:37:41 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		location;
	char	*string;

	location = -1;
	string = (char *)s;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == c)
			location = i;
		i++;
	}
	if (location != -1)
		return (string + location);
	if (string[i] == c)
		return (string + i);
	return (NULL);
}
