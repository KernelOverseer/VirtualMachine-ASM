/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:21:16 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 05:52:36 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void	ft_init_simple_colors(void)
{
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_WHITE, COLOR_WHITE);
	init_pair(7, COLOR_WHITE, COLOR_WHITE);
	init_pair(8, COLOR_WHITE, COLOR_WHITE);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_BLACK);
	init_pair(11, COLOR_WHITE, COLOR_WHITE);
}

static void	ft_init_normal_colors(void)
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_WHITE, COLOR_WHITE);
	init_pair(7, COLOR_WHITE, COLOR_WHITE);
	init_pair(8, COLOR_WHITE, COLOR_WHITE);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_WHITE);
}

void		ft_init_visualiser(t_vm_env *env)
{
	if (!(env->init.flags & FLAG_visualizer))
		return ;
	initscr();
	curs_set(0);
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	start_color();
	if (env->init.flags & FLAG_simple_visualiser)
		ft_init_simple_colors();
	else
		ft_init_normal_colors();
	ft_visualiser_draw_memory(env);
}

void		ft_visualiser_draw(t_vm_env *env)
{
	if (env->init.cycle_skip <= 0)
		env->init.cycle_skip = 1;
	if (!(env->init.flags & FLAG_visualizer) ||
		(env->settings.cycles_number % env->init.cycle_skip))
		return ;
	ft_visualiser_draw_memory(env);
	ft_visualiser_draw_info(env);
	env->init.visu_frame++;
	ft_visualiser_handle_keys(env);
}
