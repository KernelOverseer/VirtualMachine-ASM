/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:59:36 by abiri             #+#    #+#             */
/*   Updated: 2019/12/30 19:30:37 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include <stdio.h>

int ft_load_players(t_vm_env *vm_env)
{
    t_vm_player *player;

    vm_env->init.players.iterator = vm_env->init.players.first;
    while ((player = ttslist_iter_content(&(vm_env->init.players))))
    {
        if (!ft_parse_player(player))
            return (ERROR);
    }
    return (SUCCESS);
}

int ft_init_vm_settings(t_vm_env *vm_env)
{
    if (!ft_load_players(vm_env))
        return (ERROR);
    vm_env->settings.last_alive = vm_env->init.players.last->content;
    vm_env->settings.cycles_number = 0;
    vm_env->settings.lives_in_cycle = 0;
    vm_env->settings.cycles_to_die = CYCLE_TO_DIE;
    vm_env->settings.number_of_checks = 0;
    return (SUCCESS);
}

int	ft_init_env(t_vm_env *vm_env)
{
	ft_bzero(vm_env, sizeof(t_vm_env));
	ttslist_init(&(vm_env->init.players));
	ttslist_init(&(vm_env->arena.processes));
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_vm_env	vm_env;

	if (!ft_init_env(&vm_env))
		return (-1);
	if (!ft_check_args(&vm_env, argc, argv))
		return (-1);
	if (vm_env.init.players.size == 0)
	    return (ft_raise_exception(ERROR_no_players, NULL) - 1);
    if (!ft_sort_player_list(&vm_env.init.players))
        return (-1);
    ft_init_vm_settings(&vm_env);

    /*
    **  FOR DEBUG
    */

	t_vm_player *player;
	vm_env.init.players.iterator = vm_env.init.players.first;
	while ((player = ttslist_iter_content(&(vm_env.init.players))))
        printf("player from file : %s with index %d\n", player->filename, player->index);
	return (0);
}
