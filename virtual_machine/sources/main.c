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

int	ft_init_env(t_vm_env *vm_env)
{
	ft_bzero(vm_env, sizeof(t_vm_env));
	ttslist_init(&(vm_env->init.players));
	return (1);
}

int main(int argc, char **argv)
{
	t_vm_env	vm_env;

	if (!ft_init_env(&vm_env))
		return (-1);
	if (!ft_check_args(&vm_env, argc, argv))
	{
		printf("argument error\n");
		return (-1);
	}
	printf("argument parsing successful\n");
	t_vm_players_list *player;
	vm_env.init.players.iterator = vm_env.init.players.first;
	while ((player = ttslist_iter_content(&(vm_env.init.players))))
		printf("player from file : %s with index %d\n", player->filename, player->index);
	return (0);
}
