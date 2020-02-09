/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 04:29:59 by abiri             #+#    #+#             */
/*   Updated: 2020/02/09 08:25:44 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_intat	ft_read_memory_address(t_vm_arena *arena, int address, int size)
{
	t_intat	result;
	int		i;

	i = 0;
	result.int4 = 0;
	while (i < size)
	{
		address = ft_modulus(address, MEM_SIZE);
		if (size == 4)
			result.int4 |= arena->memory[address] << (((size - 1) * 8) - i * 8);
		else if (size == 2)
			result.int2 |= arena->memory[address] << (((size - 1) * 8) - i * 8);
		else
			result.int1 |= arena->memory[address] << (((size - 1) * 8) - i * 8);
		address++;
		i++;
	}
	return (result);
}

void	ft_write_memory_address(t_vm_arena *arena, int address, int size,
		int value)
{
	int i;

	i = 0;
	while (i < size)
	{
		address = ft_modulus(address, MEM_SIZE);
		arena->memory[address] = (value >> (((size - 1) * 8) - i * 8)) & 0xFF;
		address++;
		i++;
	}
}

int		ft_set_memory(t_vm_process *process, t_vm_argument *argument,
	t_intat value)
{
	t_vm_arena	*arena;

	arena = process->arena;
	if (argument->type == REG_CODE)
	{
		if (argument->value.int1 > REG_NUMBER || argument->value.int1 < 1)
			return (ERROR);
		process->registers[argument->value.int1 - 1] =
			ft_int_endian(value.int4);
	}
	else if (argument->type == IND_CODE)
	{
		ft_write_memory_address(arena,
		ft_modulus(process->current_position + argument->value.int4,
			MEM_SIZE), 4, value.int4);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int		ft_get_memory(t_vm_process *process, t_vm_argument *argument,
	int *status)
{
	t_vm_arena	*arena;

	arena = process->arena;
	*status = 1;
	if (argument->type == REG_CODE)
	{
		if (argument->value.int1 > REG_NUMBER || argument->value.int1 < 1)
			return ((*status = ERROR));
		return (ft_int_endian(process->registers[argument->value.int1 - 1]));
	}
	else if (argument->type == DIR_CODE)
	{
		if (process->operation.op_data->label_size)
			return (argument->value.int2);
		return (argument->value.int4);
	}
	else if (argument->type == IND_CODE)
	{
		return (ft_read_memory_address(arena,
			ft_modulus(process->current_position +
			argument->value.int2, MEM_SIZE), 4).int4);
	}
	return ((*status = 0));
}
