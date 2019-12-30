/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:23:32 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/15 13:17:13 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (fd != -1)
	{
		if (n < 0)
		{
			n = n * -1;
			nbr = n;
			ft_putchar_fd('-', fd);
		}
		else
			nbr = n;
		if (nbr >= 10)
		{
			ft_putnbr_fd(nbr / 10, fd);
			ft_putnbr_fd(nbr % 10, fd);
		}
		else
		{
			ft_putchar_fd(nbr + '0', fd);
		}
	}
	else
		return ;
}
