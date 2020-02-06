/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:15:00 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:22:58 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_zjmp(t_vm_env *env, t_vm_process *process)
{
	int	to_jump;
	int	status;

	(void)env;
	to_jump = ft_limit_address(ft_get_memory(process,
		&process->operation.args[0], &status));
	if (process->carry)
		process->operation.op_size = to_jump;
	return (SUCCESS);
}
