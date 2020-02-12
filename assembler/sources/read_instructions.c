/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:35:36 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/03 04:32:23 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	add_instruction(t_inst **list, t_inst *new, t_label **labels, int *num)
{
	new->line = *num;
	if (!*list)
	{
		(*list) = new;
		(*list)->tail = (*list);
		(*list)->tail->next = NULL;
	}
	else
	{
		(*list)->tail->next = new;
		(*list)->tail = (*list)->tail->next;
		(*list)->tail->next = NULL;
	}
	if (new->label)
		store_label(labels, *list);
	*num += 1;
}

/*
**	label_simple_line :
**	(!simple_line)	A) if a line contains label + inst, spaces will be != 0
**		=>			B) if a line contains only a label, spaces will be != 0
**		=>			C) if the line contain a word != label ===> spaces == 0
**	examples :	A)	labelname: live %1	|	spaces = 11 !*(line + spaces) = 'l'
**				B)	labelbame:\t \t		|	spaces = 13 !*(line + spaces) = '\0'
**				C)	notalabel			|	spaces = 0	!*(line + spaces) = '\0'
*/

int		label_simple_line(int *num, int cursor, t_asm *data, t_inst *new)
{
	if (cursor)
	{
		add_instruction(&data->instructions, new, &data->labels, num);
		return (1);
	}
	force_quit(NULL, NULL, &new);
	return (ft_raise_exception(12, NULL));
}

int		manage_inst_name(char *line, t_inst *new)
{
	char	*name;
	int		index;
	int		args;

	index = -1;
	while (g_op_tab[++index].name)
	{
		if ((name = ft_strstr(line, g_op_tab[index].name)) && !(name - line))
		{
			ft_memdel((void**)&new->name);
			new->name = ft_strdup(g_op_tab[index].name);
			new->id = index;
			args = ft_strlen(new->name) + skip_wsp(line + ft_strlen(new->name));
		}
	}
	if (new->name)
		return (args);
	return (ft_raise_exception(12, NULL));
}

/*
**	if (!cursor)			== there are no instructions.
**	if (!*(line + cursor))	== valid instructions with invalid endofline.
*/

int		get_instructions(char *line, t_asm *data, int *code)
{
	int			cursor;
	int			inst_name;
	t_inst		*new;
	static int	num;

	initialize_instruction(&new);
	if (!*line)
		return (force_quit(NULL, NULL, &new) + 2);
	if ((cursor = manage_label(line, new)) == -1)
		return (force_quit(NULL, NULL, &new));
	if (!*(line + cursor))
		return (label_simple_line(&num, cursor, data, new));
	cursor += (inst_name = manage_inst_name(line + cursor, new));
	if (!cursor || !inst_name)
		return (force_quit(NULL, NULL, &new));
	if (!*(line + cursor))
		return (ft_raise_exception(14, NULL));
	if (!(manage_arguments(line + cursor, new)))
		return (force_quit(NULL, NULL, &new));
	update_size_instruction(new);
	add_instruction(&data->instructions, new, &data->labels, &num);
	data->size_champ += new->size;
	*code = 1;
	return (1);
}
