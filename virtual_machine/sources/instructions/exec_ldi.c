/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:14:16 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:22:19 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_ldi(t_vm_env *env, t_vm_process *process)
{
	int		offset;
	int		status;
	t_intat	value;

	(void)env;
	offset = ft_get_memory(process, &process->operation.args[0], &status);
	if (process->operation.args[0].type != IND_CODE)
		offset += ft_get_memory(process, &process->operation.args[1], &status);
	offset = ft_limit_address(offset);
	value = ft_read_memory_address(&env->arena,
		process->current_position + offset, 4);
	ft_set_memory(process, &process->operation.args[2], value);
	return (SUCCESS);
}
