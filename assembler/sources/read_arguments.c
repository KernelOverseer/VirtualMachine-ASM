/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:55:40 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 04:19:10 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		store_arg_and_skip(char *line, char *separator, t_inst *new, int index)
{
	int		arg_length;
	char	*tmp;

	tmp = separator ? ft_strsub(line, 0, separator - line) : line;
	arg_length = skip_not_wsp(tmp);
	new->args[index]->name = ft_strsub(line, 0, arg_length);
	new->args[index]->type = str_type_arg(new->args[index]->name);
	separator ? ft_memdel((void**)&tmp) : 0;
	arg_length += skip_wsp(line + arg_length);
	return (arg_length);
}

int		check_3rd_arg(char *line, int index, int arg_length, t_inst *new)
{
	line = line + index + arg_length;
	if (*line == SEPARATOR_CHAR)
	{
		line += 1;
		index = skip_wsp(line);
		arg_length = skip_not_wsp(line + index);
		new->args[2]->name = ft_strsub(line + index, 0, arg_length);
		new->args[2]->type = str_type_arg(new->args[2]->name);
		if (arg_length &&
			!*(line + index + arg_length + skip_wsp(line + index + arg_length)))
			return (1);
		else
			return (ft_raise_exception(14, line));
	}
	else if (!*line)
		return (1);
	return (2);
}

int		single_or_less_argument(char *line, t_inst *new)
{
	int	arg_length;
	int	endline;

	arg_length = skip_not_wsp(line);
	new->args[0]->name = ft_strsub(line, 0, arg_length);
	new->args[0]->type = str_type_arg(new->args[0]->name);
	endline = skip_wsp(line + arg_length);
	if (!*(line + arg_length + endline))
		return (1);
	else
		return (ft_raise_exception(14, line + arg_length + endline));
}

int		multiple_args(char *line, t_inst *new, char *separator)
{
	int		arg_length;
	int		res;
	int		index;

	arg_length = store_arg_and_skip(line, separator, new, 0);
	if (line + arg_length == separator)
	{
		arg_length += skip_wsp(line + arg_length + 1) + 1;
		index = arg_length;
		if ((separator = ft_strchr(line + index, SEPARATOR_CHAR)))
		{
			arg_length = store_arg_and_skip(line + index, separator, new, 1);
			if ((res = check_3rd_arg(line, index, arg_length, new)) < 2)
				return (res);
			return (1);
		}
		if (!*(line + index))
			return (ft_raise_exception(11, NULL));
		arg_length = store_arg_and_skip(line + index, separator, new, 1);
		if (!*(line + index + arg_length))
			return (1);
		return (ft_raise_exception(14, line + index + arg_length));
	}
	return (ft_raise_exception(15, line));
}

int		manage_arguments(char *line, t_inst *new)
{
	char	*separator;

	separator = NULL;
	if ((separator = ft_strchr(line, SEPARATOR_CHAR)))
	{
		if (!(multiple_args(line, new, separator)))
			return (0);
	}
	else
	{
		if (!(single_or_less_argument(line, new)))
			return (0);
	}
	return (check_valid_args(new));
}
