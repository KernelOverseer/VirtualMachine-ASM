/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:09:46 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 06:03:36 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	ft_print_player_live(t_vm_env *env, t_vm_process *process)
{
	if ((env->init.flags & FLAG_visualizer) ||
		!(env->init.flags & FLAG_live))
		return ;
	ft_printf("A process shows that player %d (%s) is alive\n",
	process->player->index, process->player->name);
}

int		ft_exec_live(t_vm_env *env, t_vm_process *process)
{
	int			player_code;
	t_vm_player	*player;

	(void)env;
	player_code = -process->operation.args[0].value.int4;
	process->is_live = 1;
	if (player_code > 0 && player_code <= (int)env->init.players.size)
	{
		env->settings.last_alive = player_code;
		if ((player = ttslist_get_id_content(&env->init.players,
			player_code - 1)))
		{
			player->last_live = env->settings.cycles_number;
			ft_print_player_live(env, process);
			ft_visualiser_update_value(env,
				process->current_position, -player_code, 5);
		}
	}
	else
		ft_visualiser_update_value(env,
			process->current_position, -process->player->index, 5);
	process->last_live_cycle = env->settings.cycles_number;
	env->settings.lives_in_cycle++;
	return (SUCCESS);
}
