/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 22:38:16 by abiri             #+#    #+#             */
/*   Updated: 2020/01/07 22:38:17 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int    ft_int_endian(int i)
{
    return (((i >> 24) & 0xFF) | ((i >> 8) & 0xFF00) | ((i << 8) & 0xFF0000) | ((i << 24) & 0xFF000000));
}

short  ft_short_endian(short i)
{
    return ((i >> 8 | i << 8) & 0xFFFF);
}

t_intat ft_read_memory_address(t_vm_arena *arena, int address, int size)
{
    int i;
    t_intat result;

    i = 0;
    result.int4 = 0;
    while (i < size)
    {
        address %= MEM_SIZE;
        result.int4 |= arena->memory[address] << ((size * 8 - 8) - (i * 8));
        address++;
        i++;
    }
    return (result);
}

void    ft_write_memory_address(t_vm_arena *arena, int address, int size,
        int value)
{
    int i;

    i = 0;
    while (i < size)
    {
        address %= MEM_SIZE;
        arena->memory[address] = (value >> ((size * 8 - 8) - (i * 8)) & 0xFF);
        i++;
    }
}

int ft_set_memory(t_vm_process *process, t_vm_argument *argument, t_intat value)
{
    t_vm_arena  *arena;

    arena = process->arena;
    if (argument->type == REG_CODE)
    {
        if (argument->value.int1 > REG_NUMBER || argument->value.int1 < 0)
            return (ERROR);
        process->registers[argument->value.int1 - 1] = value.int4;
    }
    else if (argument->type == IND_CODE)
    {
        arena->memory[(process->current_position + argument->value.int4)
            % MEM_SIZE] = value.int1;
    }
    else
        return (ERROR);
    return (SUCCESS);
}

int ft_get_memory(t_vm_process *process, t_vm_argument *argument, int *status)
{
    t_vm_arena  *arena;

    arena = process->arena;
    *status = 1;
    if (argument->type == REG_CODE)
    {
        if (argument->value.int1 > REG_NUMBER || argument->value.int1 < 0)
            return ((*status = ERROR));
        return (process->registers[argument->value.int1 - 1]);
    }
    else if (argument->type == DIR_CODE)
    {
        if (process->operation.op_data->label_size)
            return (argument->value.int2);
        return (argument->value.int4);
    }
    else if (argument->type == IND_CODE)
    {
        return (ft_read_memory_address(arena, process->current_position +
            argument->value.int2, 4).int4);
    }
//        return (*((int *)(&arena->memory[(process->current_position +
  //      argument->value.int2) % MEM_SIZE])));

    return ((*status = 0));
}