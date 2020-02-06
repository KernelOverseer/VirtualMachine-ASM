/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:13:00 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:20:09 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	ft_init_game(t_vm_env *env)
{
	env->settings.last_alive = env->init.players.size;
	env->settings.last_period_cycles = 0;
	env->settings.cycles_number = 1;
	env->settings.lives_in_cycle = 0;
	env->settings.cycles_to_die = CYCLE_TO_DIE;
	env->settings.number_of_checks = 0;
	env->settings.number_of_checks_from_last_change = 0;
}

int		ft_load_players_on_arena(t_vm_env *vm_env)
{
	int			offset;
	int			index;
	t_vm_player	*player;

	vm_env->init.players.iterator = vm_env->init.players.first;
	offset = MEM_SIZE / vm_env->init.players.size;
	index = 0;
	while ((player = ttslist_iter_content(&(vm_env->init.players))))
	{
		ft_memcpy(vm_env->arena.memory + offset * index, player->exec_code,
				player->exec_size);
		if (!ft_add_process(vm_env, offset * index, player))
			return (ERROR);
		index++;
	}
	return (SUCCESS);
}
