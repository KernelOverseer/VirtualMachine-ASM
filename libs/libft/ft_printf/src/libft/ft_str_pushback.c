/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_pushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 05:31:52 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/10 05:31:53 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_str_pushback(char *str, char c)
{
	char	*new_str;
	int		newlen;
	int		len;

	len = ft_strlen(str);
	newlen = len + 1;
	new_str = ft_strnew(newlen);
	new_str[len] = c;
	while (len--)
		new_str[len] = str[len];
	free(str);
	return (new_str);
}
