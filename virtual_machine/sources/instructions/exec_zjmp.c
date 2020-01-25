/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:15:00 by abiri             #+#    #+#             */
/*   Updated: 2020/01/25 23:58:25 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*int	ft_wait_operation(int address, t_vm_arena *arena)
{
	int	opcode;

	opcode = arena->memory[ft_modulus(address, MEM_SIZE)];
	if (!ft_valid_opcode(opcode))
		return (0);
	return (g_op_tab[opcode - 1].cycle_number);
}*/

int	ft_exec_zjmp(t_vm_env *env, t_vm_process *process)
{
	int	to_jump;
	int	status;

	to_jump = ft_limit_address(ft_get_memory(process,
		&process->operation.args[0], &status));
//	ft_printf("jumping on %d with value %d\n", process->current_position + to_jump, env->arena.memory[ft_modulus(process->current_position + to_jump, MEM_SIZE)]);
	if (process->carry)
	{
		process->operation.op_size = to_jump;
//		process->remaining_cycles = ft_op_wait(process, process->arena) - 1;
	}
	return (SUCCESS);
}
