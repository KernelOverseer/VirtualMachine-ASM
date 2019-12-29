/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:43:16 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/21 04:33:20 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned	char	*destination;

	i = 0;
	destination = (unsigned	char *)s;
	while (i < n)
	{
		if (destination[i] == (unsigned	char)c)
		{
			s = (void *)destination;
			return (destination + i);
		}
		i++;
	}
	return (NULL);
}
