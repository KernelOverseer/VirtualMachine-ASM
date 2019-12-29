/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 15:10:03 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/17 18:01:56 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t count;

	i = 0;
	count = ft_strlen(s1);
	while (s2[i] != 0 && i < n)
	{
		s1[count + i] = s2[i];
		i++;
	}
	s1[count + i] = '\0';
	return (s1);
}
