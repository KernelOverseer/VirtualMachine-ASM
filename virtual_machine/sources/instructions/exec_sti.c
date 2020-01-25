/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:14:58 by abiri             #+#    #+#             */
/*   Updated: 2020/01/26 00:08:52 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_sti(t_vm_env *env, t_vm_process *process)
{
	int		offset;
	int		status;
	t_intat	value;

	offset = ft_get_memory(process, &process->operation.args[1], &status);
	if (process->operation.args[1].type != IND_CODE)
		offset += ft_get_memory(process, &process->operation.args[2], &status);
	offset = ft_limit_address(offset);
	//value = ft_read_memory_address(&env->arena, process->current_position + offset, 4);
	value.int4 = ft_get_memory(process, &process->operation.args[0], &status);
	ft_write_memory_address(&env->arena, process->current_position + offset, 4, value.int4);
	ft_printf("\n");
	return (SUCCESS);
}
