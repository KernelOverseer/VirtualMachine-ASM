/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 22:56:38 by aelouarg          #+#    #+#             */
/*   Updated: 2020/02/03 03:26:39 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		args_number(t_arg *args[3])
{
	int number;

	number = 0;
	while (args[number] && args[number]->name)
		number += 1;
	return (number);
}

int		is_valid_reg(t_arg *reg)
{
	if (reg->type == T_REG)
	{
		if (ft_strlen(reg->name) < 2 ||
				!ft_isint(reg->name + 1) ||
					ft_atoi(reg->name + 1) < 0 ||
						ft_atoi(reg->name + 1) > REG_NUMBER ||
							ft_atoi(reg->name + 1) > 255)
			return (ft_raise_exception(18, reg->name));
	}
	return (1);
}

int		is_valid_dir(t_arg *dir)
{
	if (dir->type == T_DIR)
	{
		if (ft_strlen(dir->name) <= 1 ||
			((dir->name + 1 && !ft_isint(dir->name + 1)) &&
				(dir->name && dir->name + 1 && *(dir->name + 1) != LABEL_CHAR)))
			return (ft_raise_exception(18, dir->name));
	}
	return (1);
}

int		is_valid_ind(t_arg *ind)
{
	if (ind->type == T_IND)
	{
		if ((ind->name + 1 && !ft_isint(ind->name + 1)) &&
			(ind->name && *ind->name != LABEL_CHAR))
			return (ft_raise_exception(18, ind->name));
	}
	return (1);
}

int		check_valid_args(t_inst *inst)
{
	int index;
	int max_arg;

	max_arg = args_number(inst->args);
	if (g_op_tab[inst->id].args_number == max_arg)
	{
		index = 0;
		while (index < max_arg)
		{
			if (!(str_type_arg(inst->args[index]->name)
				& g_op_tab[inst->id].args_type[index]))
				return (ft_raise_exception(17, inst->args[index]->name));
			if (!is_valid_reg(inst->args[index]))
				return (0);
			if (!is_valid_dir(inst->args[index]))
				return (0);
			if (!is_valid_ind(inst->args[index]))
				return (0);
			index += 1;
		}
	}
	else
		return (ft_raise_exception(16, NULL));
	return (1);
}
