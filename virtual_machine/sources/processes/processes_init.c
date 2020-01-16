/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:22:24 by abiri             #+#    #+#             */
/*   Updated: 2020/01/02 16:22:25 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_vm_process *ft_new_vm_process(int player_id)
{
    static int      process_id;
    t_vm_process    *result;

    if (!(result = ft_memalloc(sizeof(t_vm_process))))
        return (NULL + ft_raise_exception(ERROR_allocation_problem, NULL));
    result->id = process_id++;
    result->carry = FALSE;
    result->registers[0] = -player_id;
    return (result);
}

int ft_add_process(t_vm_env *env, int address, t_vm_player *player)
{
    t_vm_process    *process;

    if(!(process = ft_new_vm_process(player->index)))
        return (ERROR);
    process->arena = &(env->arena);
    process->player = player;
    process->current_position = address;
    env->arena.processes.push(&env->arena.processes, process);
    return (SUCCESS);
}