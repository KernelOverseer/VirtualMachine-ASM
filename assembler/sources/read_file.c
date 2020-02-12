/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:21:57 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/01 05:38:41 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_command(int filedesc, char *line, t_asm *data)
{
	int		name_cmd;
	int		comment_cmd;
	char	name_buffer[PROG_NAME_LENGTH + 2];
	char	comment_buffer[COMMENT_LENGTH + 2];

	ft_bzero(name_buffer, PROG_NAME_LENGTH + 2);
	ft_bzero(comment_buffer, COMMENT_LENGTH + 2);
	name_cmd = command_isname(line);
	comment_cmd = command_iscomment(line);
	if (!name_cmd && !comment_cmd)
		return (ft_raise_exception(8, line));
	else if (name_cmd && !comment_cmd)
		return (store_name_command(data, line, filedesc, name_buffer));
	else if (!name_cmd && comment_cmd)
		return (store_comment_command(data, line, filedesc, comment_buffer));
	return (0);
}

void	endline_null(char *line, int *newline)
{
	*newline = 0;
	if (*(line + ft_strlen(line) - 1) == '\n')
	{
		*(line + ft_strlen(line) - 1) = '\0';
		*newline = 1;
	}
}

int		read_line(int filedesc, t_asm *data, int *code)
{
	int		eol;
	int		skip;
	int		get;
	int		newline;
	char	*line;

	while ((eol = get_line(filedesc, &line)) > 0)
	{
		endline_null(line, &newline);
		skip = skip_wsp(line);
		if (line_to_manage(line))
		{
			ft_find_comment(line);
			if ((!(!data->cmd_name || !data->cmd_comment || line[skip] == '.'))
				&& (!(get = get_instructions(line + skip, data, code))))
				return (free_s_asm(&data, &line, 1));
			else if (!data->cmd_name || !data->cmd_comment || line[skip] == '.')
				if (!(get_command(filedesc, line + skip, data)))
					return (free_s_asm(&data, &line, 1));
		}
		ft_memdel((void**)&line);
	}
	eol >= 0 ? ft_memdel((void**)&line) : 0;
	return (!(*code) || (!newline && get != 2) ?
		ft_raise_exception(1, NULL) : 1);
}

void	write_valid_output(char *file_name)
{
	char	*name;
	char	*path;

	name = ft_strsub(file_name, 0, ft_strlen(file_name) - 2);
	path = ft_strjoin(name, ".cor");
	ft_memdel((void**)&name);
	ft_putstr("Writing output program to ");
	ft_putendl(path);
	ft_memdel((void**)&path);
}

int		read_file(int filedesc, t_asm *data)
{
	int		code;

	code = 0;
	if (!read_line(filedesc, data, &code))
		return (0);
	if (!replace_label_value(data->instructions, data, 2))
		return (0);
	write_valid_output(data->file_name);
	return (1);
}
