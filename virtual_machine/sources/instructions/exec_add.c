/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:13:57 by abiri             #+#    #+#             */
/*   Updated: 2020/01/25 21:35:13 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_add(t_vm_env *env, t_vm_process *process)
{
	int		status;
	t_intat	value;

	value.int4 = ft_get_memory(process, &process->operation.args[0], &status) +
		ft_get_memory(process, &process->operation.args[1], &status);
	if (value.int4 == 0)
		process->carry = 1;
	else
		process->carry = 0;
	ft_set_memory(process, &process->operation.args[2], value);
	return (SUCCESS);
}
