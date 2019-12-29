/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:27:18 by mherrat           #+#    #+#             */
/*   Updated: 2019/05/10 05:31:13 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*pointer;

	if ((pointer = malloc(size + 1)))
	{
		ft_memset(pointer, '\0', size + 1);
		return (pointer);
	}
	return (NULL);
}
