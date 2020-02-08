/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:21:16 by abiri             #+#    #+#             */
/*   Updated: 2020/02/08 23:41:11 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	ft_visualiser_draw_memory(t_vm_env *env)
{
	int	x;
	int	y;

	while (y < 64)
	{
		y = 0;
		while (x < 64)
		{
			mvprintw(y, x * 3, "%2.2x", env->arena.memory[y * 64 + x]);
			x++;
		}
		y++;
	}
}

int ft_init_visualiser(t_vm_env *env)
{
	initscr();
	raw();
	noecho();
	ft_visualiser_draw_memory(env);
}

void	ft_visualiser_update_value(t_vm_arena *arena, int offset, int size)
{
	int x;
	int y;
	int	index;

	index = 0;
	while (index < size)
	{
		y = offset / 64;
		x = offset % 64;
		mvprintw(y, x * 3, "%2.2x", arena->memory[y * 64 + x]);
		offset++;
		index++;
	}
}

int	ft_visualiser_draw(t_vm_env *env)
{
	ft_visualiser_handle_keys(env);
	//refresh();
}