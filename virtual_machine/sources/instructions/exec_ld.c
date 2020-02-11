/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:09:11 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 02:46:26 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_ld(t_vm_env *env, t_vm_process *process)
{
	int		status;
	t_intat	value;

	(void)env;
	value.int4 = 0;
	if (process->operation.args[0].type == IND_CODE)
		process->operation.args[0].value.int2 =
		ft_limit_address(process->operation.args[0].value.int2);
	value.int4 = ft_get_memory(process, &process->operation.args[0], &status);
	if (!status)
		return (ERROR);
	ft_set_memory(process, &process->operation.args[1], value);
	if (!value.int4)
		process->carry = 1;
	else
		process->carry = 0;
	return (SUCCESS);
}
