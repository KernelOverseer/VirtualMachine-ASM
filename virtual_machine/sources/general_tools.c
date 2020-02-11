/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 04:20:02 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 02:41:45 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_modulus(int value, int modulus)
{
	if (value < 0)
		return (modulus + value % modulus);
	else
		return (value % modulus);
}

int	ft_limit_address(int value)
{
	return (value % IDX_MOD);
}

int	ft_valid_opcode(int opcode)
{
	if (opcode > 0 && opcode <= OPERATION_COUNT)
		return (SUCCESS);
	return (ERROR);
}

int	ft_get_argument_size(t_vm_argument *arg, t_op *op_data)
{
	if (arg->type == REG_CODE)
		return (T_REG);
	if (arg->type == IND_CODE)
		return (IND_SIZE);
	if (arg->type == DIR_CODE)
		return (DIR_SIZE - (2 * op_data->label_size));
	return (0);
}

int	ft_check_arguments_errors(t_vm_argument *argument)
{
	if (argument->type == REG_CODE && (argument->value.int1 > REG_NUMBER
		|| argument->value.int1 < 1))
		return (0);
	return (1);
}
