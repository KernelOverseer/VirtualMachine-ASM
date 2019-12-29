/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:14:08 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/20 16:02:51 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char	const *s2, size_t n)
{
	size_t				i;
	unsigned	char	*string1;
	unsigned	char	*string2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (string1[i] != string2[i])
			return (0);
		i++;
	}
	return (1);
}
