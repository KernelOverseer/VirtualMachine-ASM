/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 02:10:12 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/21 02:21:35 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcasecmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0'))
	{
		if (s1[i] == s2[i])
			i++;
		else if ((s1[i] >= 'A' && s1[i] <= 'Z')
		&& (s2[i] >= 'A' && s2[i] <= 'Z'))
			return ((unsigned char)ft_tolower(s1[i])
			- (unsigned char)ft_tolower(s2[i]));
		else if ((s1[i] >= 'a' && s1[i] <= 'z')
		&& (s2[i] >= 'A' && s2[i] <= 'Z'))
			return ((unsigned char)s1[i]
			- (unsigned char)ft_tolower(s2[i]));
		else if ((s2[i] >= 'a' && s2[i] <= 'z')
		&& (s1[i] >= 'A' && s1[i] <= 'Z'))
			return ((unsigned char)ft_tolower(s1[i])
			- (unsigned char)s2[i]);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
