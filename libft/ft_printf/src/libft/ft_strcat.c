/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 05:51:41 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/21 04:56:28 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t i;
	size_t count;

	i = 0;
	count = ft_strlen(s1);
	while (s2[i] != 0)
	{
		s1[count + i] = s2[i];
		i++;
	}
	s1[count + i] = '\0';
	return (s1);
}
