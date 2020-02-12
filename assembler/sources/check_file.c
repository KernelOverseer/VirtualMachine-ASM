/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 04:51:53 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/02 02:14:26 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_extension(char *filename)
{
	size_t	length;

	length = ft_strlen(filename);
	if (length >= 2)
	{
		if (!(filename[length - 1] == 's' && filename[length - 2] == '.'))
			return (0);
		return (1);
	}
	return (0);
}

int		open_file(char *filename)
{
	int	filedesc;

	errno = 0;
	filedesc = open(filename, O_RDONLY);
	if (errno)
		return (-1);
	return (filedesc);
}

int		read_args(char *filename, t_asm *data)
{
	int		filedesc;

	filedesc = open_file(filename);
	if (filedesc >= 0)
	{
		initialize_asm(&data, filename);
		if (!errno)
		{
			if (!read_file(filedesc, data))
			{
				return (0);
			}
			close(filedesc);
			return (1);
		}
	}
	ft_raise_exception(19, strerror(errno));
	return (0);
}

int		parse_args(char *filename, t_asm *data)
{
	errno = 0;
	if (check_extension(filename))
	{
		if (read_args(filename, data))
			return (1);
		free_s_asm(&data, NULL, 0);
		free_s_asm_node(&data);
		return (0);
	}
	free_s_asm(&data, NULL, 0);
	free_s_asm_node(&data);
	return (ft_raise_exception(0, filename));
}
