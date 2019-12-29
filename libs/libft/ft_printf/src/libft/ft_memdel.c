/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 15:48:43 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/19 22:21:20 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdel(void **ap)
{
	unsigned char **pointer;

	if (ap == NULL)
		return ;
	pointer = (unsigned char **)ap;
	if (*pointer != NULL)
	{
		free(*pointer);
		*pointer = NULL;
	}
}
