/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:14:56 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:22:50 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_sub(t_vm_env *env, t_vm_process *process)
{
	int		status;
	t_intat	value;

	(void)env;
	value.int4 = ft_get_memory(process, &process->operation.args[0], &status) -
		ft_get_memory(process, &process->operation.args[1], &status);
	if (value.int4 == 0)
		process->carry = 1;
	else
		process->carry = 0;
	ft_set_memory(process, &process->operation.args[2], value);
	return (SUCCESS);
}
