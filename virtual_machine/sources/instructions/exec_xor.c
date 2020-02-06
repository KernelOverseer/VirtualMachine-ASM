/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:14:54 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:22:53 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_xor(t_vm_env *env, t_vm_process *process)
{
	int		status;
	t_intat	first;
	t_intat	second;
	t_intat	result;

	(void)env;
	first.int4 = ft_get_memory(process, &process->operation.args[0], &status);
	second.int4 = ft_get_memory(process, &process->operation.args[1], &status);
	result.int4 = first.int4 ^ second.int4;
	ft_set_memory(process, &process->operation.args[2], result);
	if (result.int4 == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (SUCCESS);
}
