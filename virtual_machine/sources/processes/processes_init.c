/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:21:51 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 15:22:57 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_vm_process	*ft_new_vm_process(int player_id)
{
	static int		process_id;
	t_vm_process	*result;

	if (!(result = ft_memalloc(sizeof(t_vm_process))))
		return (NULL + ft_raise_exception(ERROR_allocation_problem, NULL));
	result->id = process_id++;
	result->carry = FALSE;
	result->registers[0] = ft_int_endian(-player_id);
	result->last_position = -1;
	result->operation.op_size = 1;
	return (result);
}

int				ft_add_process(t_vm_env *env, int address, t_vm_player *player)
{
	t_vm_process	*process;

	if (!(process = ft_new_vm_process(player->index)))
		return (ERROR);
	process->arena = &(env->arena);
	process->player = player;
	process->current_position = address;
	process->born_cycle = env->settings.cycles_number;
	env->arena.processes.push_front(&env->arena.processes, process);
	return (SUCCESS);
}
