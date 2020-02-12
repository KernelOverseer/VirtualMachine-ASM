/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:41:52 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/01 05:30:41 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		store_command(int fd, char *line, char *buffer, size_t buffsize)
{
	int		inquote;
	int		index;
	size_t	buffer_index;
	int		f;

	initialize_variables(buffer, &inquote, &index, &buffer_index);
	buffer_index ? inquote = 1 : 0;
	replace_newline(line);
	while (line[++index])
	{
		if (!inquote &&
			(line[index] == COMMENT_CHAR || line[index] == COMMENT_CHAR_2))
			return (2);
		if (!(f = get_inquote(line + index, &inquote, buffer, buffsize)))
			return (0);
		if (f == 1)
			buffer_index += 1;
	}
	if (inquote)
	{
		buffer[buffer_index] = '\n';
		return (get_multi_line(fd, inquote, buffer, buffsize));
	}
	return (check_buffer_size(buffsize, buffer_index));
}

int		store_name_command(t_asm *data, char *line,
		int filedesc, char *command_buffer)
{
	char	*command;

	if (data->cmd_name)
		return (ft_raise_exception(3, NULL));
	command = line + ft_strlen(NAME_CMD_STRING)
			+ skip_wsp(line + ft_strlen(NAME_CMD_STRING));
	if (!store_command(filedesc, command, command_buffer, PROG_NAME_LENGTH))
		return (0);
	data->cmd_name = ft_strdup(command_buffer);
	return (1);
}

int		store_comment_command(t_asm *data, char *line,
		int filedesc, char *command_buffer)
{
	char	*command;
	int		store;

	store = 0;
	if (data->cmd_comment)
		return (ft_raise_exception(4, NULL));
	command = line + ft_strlen(COMMENT_CMD_STRING)
			+ skip_wsp(line + ft_strlen(COMMENT_CMD_STRING));
	if (!(store = store_command(filedesc, command, command_buffer,
		COMMENT_LENGTH)))
		return (0);
	else if (store == -1)
		return (ft_raise_exception(5, NULL));
	data->cmd_comment = ft_strdup(command_buffer);
	return (1);
}
