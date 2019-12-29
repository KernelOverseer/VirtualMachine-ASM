/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 05:32:18 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/10 05:32:19 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcnew(size_t size, char c)
{
	char	*str;

	str = ft_strnew(size);
	while (size--)
		str[size] = c;
	return (str);
}
