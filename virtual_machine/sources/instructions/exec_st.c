/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:10:25 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 04:08:01 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_st(t_vm_env *env, t_vm_process *process)
{
	t_intat value;
	int		status;

	(void)env;
	status = SUCCESS;
	value.int4 = ft_get_memory(process, &process->operation.args[0], &status);
	if (!status)
		return (ERROR);
	if (process->operation.args[1].type == IND_CODE)
		process->operation.args[1].value.int2 %= IDX_MOD;
	if (!ft_set_memory(process, &process->operation.args[1], value))
		return (ERROR);
	if (process->operation.args[1].type == IND_CODE)
		ft_visualiser_update_value(env,
			process->current_position + process->operation.args[1].value.int2,
			-process->player->index, 4);
	return (SUCCESS);
}
