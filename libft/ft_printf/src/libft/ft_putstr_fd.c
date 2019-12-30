/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 23:04:46 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/19 22:20:49 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (fd != -1)
	{
		if (s == NULL)
			return ;
		while (*s != '\0')
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
	else
		return ;
}
