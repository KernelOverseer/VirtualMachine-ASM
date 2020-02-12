/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_labels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:48:17 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/03 04:30:38 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		valid_label(char *line, char *label, t_inst *inst)
{
	int index;
	int	ischarin;

	index = 0;
	if ((ischarin = ft_ischarin(LABEL_CHARS, *(label - 1))))
	{
		inst->label = ft_strsub(line, 0, label - line);
		while (inst->label[index])
		{
			if (!ft_ischarin(LABEL_CHARS, inst->label[index]))
			{
				ft_raise_exception(13, NULL);
				return (-1);
			}
			index += 1;
		}
	}
	else
		return (0);
	return (index);
}

/*
**	This function check if there's a label separator, otherwise it returns 0
**	else it checks if the label is valid or not;
*/

int		manage_label(char *line, t_inst *inst)
{
	int		index;
	char	*label;

	index = 0;
	if ((label = ft_strchr(line, LABEL_CHAR)))
	{
		if ((index = valid_label(line, label, inst)) < 1)
			return (index);
	}
	else
		return (0);
	if (!inst->label)
		return (0);
	index += 1;
	index += skip_wsp(line + index);
	return (index);
}

/*
**	This function add a pointer to an instruction (node)
**	whenever a label is found.
**	The first node contains the size of the array: (id);
*/

void	store_label(t_label **labels, t_inst *list)
{
	int	id;

	if (!*labels)
	{
		allocate_label(labels);
		(*labels)->id = 1;
		(*labels)[0].addr = list->tail;
	}
	else
	{
		id = (*labels)->id;
		(*labels)->id += 1;
		if (!((*labels) = (t_label *)
			realloc(*labels, (*labels)->id * sizeof(t_label))))
			exit(-1);
		(*labels)[id].addr = list->tail;
	}
}
