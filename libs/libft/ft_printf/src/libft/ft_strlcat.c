/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 15:54:31 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/18 14:04:50 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count_dest;
	size_t	count_src;

	count_dest = 0;
	count_src = ft_strlen(src);
	while (*dst != 0 && size > 0)
	{
		dst++;
		count_dest++;
		size--;
	}
	while (*src != 0 && size > 1)
	{
		size--;
		*dst++ = *src++;
	}
	while (*src == '\0' && size > 1)
	{
		size--;
		*dst++ = '\0';
	}
	if (size == 1)
		*dst = '\0';
	return (count_src + count_dest);
}
