/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:39:42 by abiri             #+#    #+#             */
/*   Updated: 2020/02/09 01:18:27 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		ft_get_arguments_types(t_vm_process *process,
	t_vm_arena *arena)
{
	t_op			*op_data;
	int				index;
	int				offset;
	int				current_error;
	unsigned char	type_byte;

	index = 0;
	current_error = 0;
	offset = 1;
	op_data = &g_op_tab[process->operation.op_code - 1];
	type_byte = arena->memory[ft_modulus(process->current_position +
		offset, MEM_SIZE)];
	while (index < op_data->args_number)
	{
		process->operation.args[index].type =
			(((type_byte >> (6 - 2 * index)) & 0b11));
		if (!(op_data->args_type[index] & (1 <<
			(process->operation.args[index].type - 1))))
			current_error = 1;
		offset += ft_get_argument_size(&process->operation.args[index],
			op_data);
		index++;
	}
	process->operation.op_size = offset + 1;
	return (!current_error);
}

int		ft_load_arguments_types(t_vm_process *process)
{
	t_op	*op_data;
	int		index;

	index = 0;
	op_data = &g_op_tab[process->operation.op_code - 1];
	while (index < op_data->args_number)
	{
		process->operation.args[index].type = op_data->args_type[index];
		process->operation.op_size += ft_get_argument_size(
			&process->operation.args[index], op_data);
		index++;
	}
	return (SUCCESS);
}

int		ft_load_arguments_value(t_vm_process *process, t_vm_arena *arena)
{
	t_op			*op_data;
	int				index;
	int				size;
	int				offset;
	int				result;

	index = 0;
	op_data = &g_op_tab[process->operation.op_code - 1];
	offset = (op_data->octet_codage ? 1 : 0) + 1;
	result = 1;
	size = 0;
	while (index < op_data->args_number)
	{
		size = ft_get_argument_size(&process->operation.args[index], op_data);
		process->operation.args[index].value = ft_read_memory_address(arena,
			(process->current_position + offset) % MEM_SIZE,
			size);
		result &= ft_check_arguments_errors(&process->operation.args[index]);
		offset += size;
		index++;
	}
	return (result);
}

int		ft_parse_operation_arguments(t_vm_process *process, t_vm_arena *arena)
{
	t_op	*op_data;

	op_data = &g_op_tab[process->operation.op_code - 1];
	process->operation.op_size = 1;
	if (op_data->octet_codage)
	{
		if (!ft_get_arguments_types(process, arena))
			return (ERROR);
	}
	else if (!ft_load_arguments_types(process))
		return (ERROR);
	if (!ft_load_arguments_value(process, arena))
		return (ERROR);
	process->operation.op_data = op_data;
	return (SUCCESS);
}

int		ft_parse_operation(t_vm_process *process, t_vm_arena *arena)
{
	t_vm_operation	*operation;

	operation = &(process->operation);
	operation->op_code =
		arena->memory[ft_modulus(process->current_position, MEM_SIZE)];
	if (!ft_valid_opcode(operation->op_code))
		return (ERROR);
	if (!ft_parse_operation_arguments(process, arena))
		return (ERROR);
	return (SUCCESS);
}
