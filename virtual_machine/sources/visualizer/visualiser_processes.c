/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 07:18:55 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 21:42:21 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	ft_visualiser_update_value(t_vm_env *env, int offset,
	int color, int size)
{
	int	index;

	if (env->init.cycle_skip <= 0)
		env->init.cycle_skip = 1;
	if (!(env->init.flags & FLAG_visualizer))
		return ;
	if (env->settings.cycles_number % env->init.cycle_skip
		&& color > MAX_PLAYERS)
		color = color - MAX_PLAYERS;
	index = 0;
	while (index < size)
	{
		offset = ft_modulus(offset, MEM_SIZE);
		env->arena.colors[offset] = color;
		index++;
		offset++;
	}
}

void	ft_visualiser_highlight_process(t_vm_env *env, t_vm_process *process)
{
	int	color;

	if (env->settings.cycles_number % env->init.cycle_skip)
		return ;
	color = env->arena.colors[ft_modulus(process->current_position, MEM_SIZE)];
	if (color <= MAX_PLAYERS && color > 0)
		color += 4;
	else if (color == 0)
		color = RAW_CURSOR_MODE;
	env->arena.colors[ft_modulus(process->current_position, MEM_SIZE)] = color;
}

void	ft_visualiser_unhighlight_process(t_vm_env *env, t_vm_process *process)
{
	int	color;

	color = env->arena.colors[ft_modulus(process->current_position, MEM_SIZE)];
	if (color == RAW_CURSOR_MODE)
		color = 0;
	else if (color > MAX_PLAYERS && color < 9)
		color -= 4;
	env->arena.colors[ft_modulus(process->current_position, MEM_SIZE)] = color;
}

void	ft_visualiser_handle_keys(t_vm_env *env)
{
	int c;

	c = 0;
	while (c != ' ' && c != 's')
	{
		c = getch();
		if (c == KEY_LEFT || c == KEY_RIGHT)
			env->init.cycle_skip += (c == KEY_LEFT) ? -5 : 5;
		else if (c == KEY_UP || c == KEY_DOWN)
			env->init.cycle_skip += (c == KEY_UP) ? 50 : -50;
		else if (c == ' ')
			env->init.visu_stop = -env->init.visu_stop;
		else if (c == 's')
			env->init.cycle_skip = 1;
		if (env->init.cycle_skip <= 0)
			env->init.cycle_skip = 1;
		ft_visualiser_draw_info(env);
		if (env->init.visu_stop >= 0)
			break ;
	}
	timeout(env->init.visu_stop);
}
