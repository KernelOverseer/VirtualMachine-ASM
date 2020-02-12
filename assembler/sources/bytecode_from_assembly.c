/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_from_assembly.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 04:05:28 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/03 10:35:08 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_code(int type)
{
	if (type == T_REG)
		return (REG_CODE);
	if (type == T_IND)
		return (IND_CODE);
	if (type == T_DIR)
		return (DIR_CODE);
	return (0);
}

void	write_atc(int filedesc, t_inst *inst)
{
	char	value[4];
	char	atc;

	value[3] = 0;
	value[2] = get_code(inst->args[2]->type) << 2;
	value[1] = get_code(inst->args[1]->type) << 4;
	value[0] = get_code(inst->args[0]->type) << 6;
	atc = value[0] | value[1] | value[2] | value[3];
	ft_write_bytes(filedesc, (unsigned char *)&atc, 1);
}

void	write_arguments(int filedesc, t_inst *inst)
{
	int		index;
	int		value;
	char	*name;

	index = -1;
	while (++index < 3)
	{
		if (inst->args[index]->name)
		{
			if (inst->args[index]->type == T_REG)
			{
				value = ft_atoi(inst->args[index]->name + 1);
				ft_write_bytes(filedesc, (unsigned char*)&value, 1);
				continue ;
			}
			name = inst->args[index]->name;
			if (inst->args[index]->type == T_DIR &&
				type_size(inst->args[index]->type, inst->id) == 2)
				ft_write_short(filedesc, ft_atoi(name + 1));
			else if (inst->args[index]->type == T_IND)
				ft_write_short(filedesc, ft_atoi(name));
			else
				ft_write_int(filedesc, ft_atoi(name + 1));
		}
	}
}

void	write_instructions(int filedesc, t_inst *inst)
{
	while (inst)
	{
		if (inst->name)
		{
			ft_write_bytes(filedesc,
			(unsigned char*)&(g_op_tab[inst->id].op_code), 1);
			if (g_op_tab[inst->id].octet_codage)
				write_atc(filedesc, inst);
			write_arguments(filedesc, inst);
		}
		inst = inst->next;
	}
}
