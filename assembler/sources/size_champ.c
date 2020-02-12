/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 03:14:11 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/31 22:31:50 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_label_line(t_asm *data, t_inst *inst, int id, int *error)
{
	int		index;
	t_label	*label;
	char	*value;

	label = data->labels;
	index = 0;
	value = NULL;
	while (index < label->id)
	{
		if (ft_strequ(label[index].addr->label,
			*(inst->args[id]->name) == LABEL_CHAR ?
				inst->args[id]->name + 1 : inst->args[id]->name + 2))
			return (label[index].addr->line - inst->line);
		index += 1;
	}
	*error = 1;
	value = ft_itoa(inst->line);
	ft_raise_exception(7, value);
	ft_memdel((void**)&value);
	return (0);
}

void	replace_by_type(t_inst *inst, int index, int value)
{
	char	tab[2];
	char	*itoa_value;

	itoa_value = NULL;
	ft_memdel((void**)&(inst->args[index]->name));
	if (inst->args[index]->type == T_DIR)
	{
		tab[0] = DIRECT_CHAR;
		tab[1] = '\0';
		itoa_value = ft_itoa(value);
		inst->args[index]->name = ft_strjoin(tab, itoa_value);
		ft_memdel((void**)&(itoa_value));
	}
	else
		inst->args[index]->name = ft_itoa(value);
}

int		replace_label_value(t_inst *inst, t_asm *data, int index)
{
	int		diff_line;
	char	*name;
	int		error;
	int		value;

	error = 0;
	if (!inst)
		return (1);
	if (index < 0)
		return (replace_label_value(inst->next, data, 2));
	if (inst->args[index])
	{
		name = inst->args[index]->name;
		if ((name && name + 1 && *(name + 1) == LABEL_CHAR) ||
			(name && *name == LABEL_CHAR))
		{
			diff_line = get_label_line(data, inst, index, &error);
			if (error)
				return (0);
			value = get_value(data, inst->line, diff_line);
			ft_memdel((void**)&(inst->args[index]->name));
			replace_by_type(inst, index, value);
		}
	}
	return (replace_label_value(inst, data, index - 1));
}
