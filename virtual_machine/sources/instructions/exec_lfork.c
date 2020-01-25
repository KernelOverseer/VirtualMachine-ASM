/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:14:17 by abiri             #+#    #+#             */
/*   Updated: 2020/01/25 20:06:09 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void	ft_copy_process(t_vm_process *parent, t_vm_process *new)
{
	int index;

	new->carry = parent->carry;
	new->arena = parent->arena;
	new->last_live_cycle = parent->last_live_cycle;
	new->player = parent->player;
	index = -1;
	while (++index < REG_NUMBER)
		new->registers[index] = parent->registers[index];
	new->remaining_cycles = 1;
}

int	ft_exec_lfork(t_vm_env *env, t_vm_process *process)
{
	t_vm_process	*new_process;
	int				status;
	int				new_addr;

	new_addr = ft_get_memory(process, &process->operation.args[0], &status);
	new_addr = (new_addr + process->current_position);
	ft_add_process(env, new_addr, process->player);
	new_process = env->arena.processes.last->content;
	ft_copy_process(process, new_process);
	return (SUCCESS);
}