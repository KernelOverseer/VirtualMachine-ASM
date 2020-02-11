/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:47:25 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 07:21:48 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_execute_instruction(t_vm_env *env, t_vm_process *process, t_vm_arena
	*arena)
{
	if (process->operation.op_data ||
		(ft_valid_opcode(process->operation.op_code) &&
			ft_get_arguments_types(process, arena)))
	{
		process->operation.op_size = 1;
		ft_bzero(&process->operation.args, sizeof(process->operation.args));
		if (ft_parse_operation_arguments(process, arena))
			process->operation.op_data->exec(env, process);
	}
	else
	{
		process->operation.op_code = arena->memory[process->current_position];
		if (ft_valid_opcode(process->operation.op_code))
			ft_get_arguments_types(process, arena);
		else
			process->operation.op_size = 1;
	}
	ft_bzero(&process->operation.args, sizeof(t_vm_argument) * 4);
	process->operation.op_data = NULL;
	return (SUCCESS);
}
