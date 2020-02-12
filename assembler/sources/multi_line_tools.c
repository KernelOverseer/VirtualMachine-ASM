/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 05:30:24 by aelouarg          #+#    #+#             */
/*   Updated: 2020/02/01 05:30:32 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
** // ft_memdel((void**)newline);
**	after if;
*/

int		check_buffer_size(int buffsize, int buffer_index)
{
	char *value;

	value = NULL;
	if (buffer_index > buffsize)
	{
		value = ft_itoa(buffsize);
		ft_raise_exception(6, value);
		ft_memdel((void**)&value);
		return (0);
	}
	return (1);
}

char	*initialize_variables(char *buffer, int *inquote,
		int *index, size_t *buffer_index)
{
	*index = -1;
	*inquote = 0;
	*buffer_index = ft_strlen(buffer);
	return (NULL);
}

int		get_inquote(char *line, int *inquote, char *buffer, size_t buffsize)
{
	char	*newline;

	newline = NULL;
	if (*line == '"')
		*inquote ^= 1;
	else if (*inquote)
	{
		if (ft_strlen(buffer) >= buffsize)
		{
			ft_memdel((void**)&newline);
			newline = ft_itoa(buffsize);
			ft_raise_exception(6, newline);
			ft_memdel((void**)&newline);
			return (0);
		}
		buffer[ft_strlen(buffer)] = *line;
		return (1);
	}
	else if (!ft_strrchr(WHITESPACES, *line))
	{
		ft_memdel((void**)&newline);
		return (ft_raise_exception(8, line));
	}
	return (2);
}

int		multi_line_content(int inquote, int filedesc,
		int buffsize, char *buffer)
{
	char *newline;

	*buffer = '\n';
	if (get_line(filedesc, &newline) < 1)
		return (-1);
	if (*(newline + ft_strlen(newline) - 1) == '\n')
		*(newline + ft_strlen(newline) - 1) = '\0';
	inquote = store_command(filedesc, newline, buffer, buffsize);
	ft_memdel((void**)&newline);
	return (inquote);
}

int		get_multi_line(int fd, int inquote, char *buffer, size_t buffsize)
{
	char *newline;

	newline = NULL;
	if (get_line(fd, &newline) < 1)
		return (-1);
	replace_newline(newline);
	inquote = store_command(fd, newline, buffer, buffsize);
	ft_memdel((void**)&newline);
	return (inquote);
}
