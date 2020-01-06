/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 14:49:33 by abiri             #+#    #+#             */
/*   Updated: 2020/01/02 14:49:34 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "virtual_machine.h"

int ft_load_players_on_arena(t_vm_env *vm_env)
{
    int             offset;
    int             index;
    t_vm_player     *player;

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