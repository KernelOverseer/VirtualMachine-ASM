/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 15:02:02 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/17 20:35:57 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t count;
	size_t count2;

	i = 0;
	j = 0;
	count = ft_strlen(needle);
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		count2 = 0;
		while (needle[j] != '\0' && (j + i) < len)
		{
			if (haystack[i + j] == needle[j])
				count2++;
			if (count == count2)
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
