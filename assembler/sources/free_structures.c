/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:24:16 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/31 23:48:47 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	free_s_instructions(t_inst **inst)
{
	t_inst	*tmp;

	if (inst && *inst)
	{
		while (*inst)
		{
			tmp = *inst;
			*inst = (*inst)->next;
			ft_memdel((void**)&tmp->label);
			ft_memdel((void**)&tmp->name);
			ft_memdel((void**)&tmp->args[0]->name);
			ft_memdel((void**)&(tmp->args[0]));
			ft_memdel((void**)&tmp->args[1]->name);
			ft_memdel((void**)&(tmp->args[1]));
			ft_memdel((void**)&tmp->args[2]->name);
			ft_memdel((void**)&(tmp->args[2]));
			ft_memdel((void**)&tmp);
		}
	}
}

int		free_s_asm_node(t_asm **data)
{
	ft_memdel((void**)data);
	return (0);
}

int		free_s_label(t_label **labels)
{
	int	index;

	index = 0;
	if (labels && *labels)
	{
		while (index < (*labels)->id)
		{
			if ((*labels))
			{
				ft_memdel((void**)&(((*labels)[index])));
			}
			index += 1;
		}
	}
	return (0);
}

int		free_s_asm(t_asm **data, char **line, int permission)
{
	if (data && *data)
	{
		ft_memdel((void**)&(*data)->cmd_comment);
		ft_memdel((void**)&(*data)->cmd_name);
		free_s_instructions(&(*data)->instructions);
		ft_memdel((void**)&(*data)->labels);
	}
	permission ? ft_memdel((void**)line) : 0;
	return (0);
}

int		force_quit(char *line, t_asm **data, t_inst **inst)
{
	line ? ft_memdel((void**)&line) : 0;
	data && (*data)->labels ? ft_memdel((void**)&(*data)->labels) : 0;
	free_s_instructions(inst);
	return (0);
}
