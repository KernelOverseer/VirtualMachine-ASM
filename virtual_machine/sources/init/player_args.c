/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:20:52 by abiri             #+#    #+#             */
/*   Updated: 2020/01/01 16:09:34 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_player_add_order(void *env, int flag_index, char **params)
{
	t_vm_env			*vm_env;
	t_vm_players_list	*player;
	int					player_index;

	(void)flag_index;
	vm_env = env;
	if (!params[0] || !params[1])
		return (0);
	if (!ft_parse_int(params[0], &player_index))
		return (0);
	if (!(player = ft_memalloc(sizeof(t_vm_players_list))))
		return (0);
	player->index = player_index;
	player->filename = params[1];
	if (!(vm_env->init.players.push(&(vm_env->init.players), player)))
		return (0);
	return (3);
}

int	ft_add_new_player(t_vm_env	*vm_env, char *filename)
{
	t_vm_players_list	*player;

	if (!filename)
		return (0);
	if (!(player = ft_memalloc(sizeof(t_vm_players_list))))
		return (0);
	player->index = PLAYER_INDEX_NONE;
	player->filename = filename;
	if (!(vm_env->init.players.push(&(vm_env->init.players), player)))
		return (0);
	return (1);
}
