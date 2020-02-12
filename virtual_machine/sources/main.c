/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:18:56 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 05:09:26 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flag_processing.h"
#include "virtual_machine.h"

int		ft_load_players(t_vm_env *vm_env)
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

int		ft_init_env(t_vm_env *vm_env)
{
	ft_bzero(&(vm_env->arena.memory), MEM_SIZE);
	ttslist_init(&(vm_env->init.players));
	ttslist_init(&(vm_env->arena.processes));
	return (SUCCESS);
}

void	ft_announce_players(t_vm_env *env)
{
	t_vm_player *player;

	if (env->init.flags & FLAG_visualizer)
		return ;
	ft_printf("Introducing contestants...\n");
	env->init.players.iterator = env->init.players.first;
	while ((player = ttslist_iter_content(&env->init.players)))
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		player->index, player->exec_size, player->name, player->comment);
}

void	ft_announce_winner(t_vm_env *env)
{
	t_vm_player *player;

	if (env->init.flags & FLAG_dump)
		return ;
	env->init.players.iterator = env->init.players.first;
	while ((player = ttslist_iter_content(&env->init.players)))
	{
		if (player->index == env->settings.last_alive)
		{
			if (env->init.flags & FLAG_visualizer)
			{
				ft_visualiser_draw_winners(env, player);
				endwin();
				return ;
			}
			ft_printf("Contestant %d, \"%s\", has won !\n",
				player->index, player->name);
			break ;
		}
	}
}

int		main(int argc, char **argv)
{
	t_vm_env	*vm_env;

	if (!(vm_env = ft_memalloc(sizeof(t_vm_env))))
		return (-1 + ft_raise_exception(ERROR_allocation_problem, NULL));
	if (!ft_init_env(vm_env))
		return (-1);
	if (!ft_check_args(vm_env, argc, argv))
		return (-1);
	if (vm_env->init.players.size == 0)
		return (ft_raise_exception(ERROR_no_players, NULL) - 1);
	if (!ft_sort_player_list(&vm_env->init.players))
		return (-1);
	if (!ft_init_vm_settings(vm_env))
		return (-1);
	ft_init_visualiser(vm_env);
	if (!ft_load_players_on_arena(vm_env))
		return (-1);
	ft_announce_players(vm_env);
	ft_visualiser_draw(vm_env);
	ft_main_vm_loop(vm_env);
	ft_announce_winner(vm_env);
	return (0);
}
