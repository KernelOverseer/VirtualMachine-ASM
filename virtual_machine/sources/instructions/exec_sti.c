/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:14:58 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 07:13:54 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_sti(t_vm_env *env, t_vm_process *process)
{
	int		offset;
	int		status;
	t_intat	value;

	(void)env;
	offset = ft_get_memory(process, &process->operation.args[1], &status);
	offset += ft_get_memory(process, &process->operation.args[2], &status);
	offset = ft_limit_address(offset);
	value.int4 = ft_get_memory(process, &process->operation.args[0], &status);
	ft_write_memory_address(&env->arena,
		process->current_position + offset, 4, value.int4);
	ft_visualiser_update_value(env, process->current_position + offset,
		-process->player->index, 4);
	return (SUCCESS);
}
