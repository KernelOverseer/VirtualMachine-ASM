/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:00:47 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/21 04:57:13 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
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
	while (haystack[i] != '\0')
	{
		j = 0;
		count2 = 0;
		while (needle[j] != '\0')
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
