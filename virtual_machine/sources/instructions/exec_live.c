/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:09:46 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:23:22 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_live(t_vm_env *env, t_vm_process *process)
{
	int player_code;

	(void)env;
	player_code = -process->operation.args[0].value.int4;
	process->is_live = 1;
	if (player_code > 0 || player_code <= (int)env->init.players.size)
		env->settings.last_alive = player_code;
	process->last_live_cycle = env->settings.cycles_number;
	env->settings.lives_in_cycle++;
	return (SUCCESS);
}
