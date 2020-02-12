/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 04:03:14 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/03 10:48:12 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_write_int(int filedesc, int value)
{
	value = ((value & 0xFF000000) >> 24) |
		((value & 0x00FF0000) >> 8) | ((value & 0x0000FF00) << 8) |
		((value & 0x000000FF) << 24);
	write(filedesc, &value, sizeof(int));
}

void	ft_write_short(int filedesc, short value)
{
	value = ((value & 0xFF00) >> 8) | ((value & 0xFF) << 8);
	write(filedesc, &value, sizeof(short));
}

void	ft_write_bytes(int filedesc, unsigned char *bytes, size_t size)
{
	write(filedesc, bytes, size);
}
