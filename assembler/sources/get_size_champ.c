/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 04:47:53 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/01 05:49:12 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_inst	*iter_in_instructions(t_inst *instructions, int iter_number)
{
	while (iter_number && instructions)
	{
		instructions = instructions->next;
		iter_number -= 1;
	}
	if (iter_number && !instructions)
		return (NULL);
	return (instructions);
}

int		label_name_before_call(t_asm *data, int current_line, int position)
{
	int		result;
	t_inst	*current_inst;

	result = 0;
	current_inst = iter_in_instructions(data->instructions, current_line);
	while (position && current_inst)
	{
		result += current_inst->size;
		current_inst = current_inst->next;
		position -= 1;
	}
	return (result);
}

int		label_name_after_call(t_asm *data, int current_line, int position)
{
	int		result;
	t_inst	*current_inst;

	result = 0;
	current_inst = iter_in_instructions(data->instructions,
	position + current_line);
	while (current_inst && position < 0)
	{
		while (current_inst && !current_inst->name)
		{
			position += 1;
			current_inst = current_inst->next;
		}
		if (!position || !current_inst)
			break ;
		result += current_inst->size;
		current_inst = current_inst->next;
		position += 1;
	}
	return (-result);
}

int		get_value(t_asm *data, int current_line, int position)
{
	if (position > 0)
		return (label_name_before_call(data, current_line, position));
	return (label_name_after_call(data, current_line, position));
}

int		update_size_instruction(t_inst *inst)
{
	int		index;

	if (inst)
	{
		inst->size = 1;
		index = 0;
		while (index < 3)
		{
			inst->size += type_size(inst->args[index]->type, inst->id);
			index += 1;
		}
		inst->size += (g_op_tab[inst->id].octet_codage ? 1 : 0);
	}
	return (0);
}
