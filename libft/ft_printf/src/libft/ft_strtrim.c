/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:28:37 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/22 15:01:57 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define HASSPACES(X) (((X) == ' ' || (X) == '\n' || (X) == '\t') ? 1 : 0)

char	*ft_strtrim(char const *s)
{
	char	*string;
	size_t	end;
	size_t	start;

	if (s == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while (HASSPACES(s[start]))
		start++;
	if (start == end + 1)
	{
		if (!(string = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		string[0] = '\0';
		return (string);
	}
	while (HASSPACES(s[end]))
		end--;
	if ((string = (char *)malloc(sizeof(char) * (end - start) + 2)))
	{
		string = ft_strsub(s, start, end - start + 1);
		return (string);
	}
	return (NULL);
}
