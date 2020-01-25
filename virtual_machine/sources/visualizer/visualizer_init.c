/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   visualizer_init.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abiri <abiri@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/02 14:00:20 by abiri			 #+#	#+#			 */
/*   Updated: 2020/01/19 03:00:07 by abiri			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "virtual_machine.h"

int ft_draw_processes(t_vm_env *env)
{
	t_vm_process	*process;
	int			 x;
	int			 y;

	env->arena.processes.iterator = env->arena.processes.first;
	while ((process = ttslist_iter_content(&(env->arena.processes))))
	{
		y = process->current_position / 64;
		x = process->current_position % 64;
		attron(COLOR_PAIR(5));
		mvprintw(y, x * 3, "%2.2x",
				env->arena.memory[process->current_position]);
		attroff(COLOR_PAIR(5));
		mvprintw(0, 64 * 3 + 1, "PC	: %d\n", process->current_position);
		mvprintw(1, 64 * 3 + 1, "CYCLE : %d\n", env->settings.cycles_number);
	}
	mvprintw(2, 64 * 3 + 1, "PROCESSES : %zu\n", env->arena.processes.size);
	return (SUCCESS);
}

int ft_visualizer_init(t_vm_env *vm_env)
{
	int index;
	int jndex;
	int color;
	static  int init = 0;

	if (!init)
	{
		initscr();
		noecho();
		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_RED, COLOR_BLACK);
		init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(5, COLOR_BLACK, COLOR_WHITE);
	}
	index = 0;
	while (index < MEM_SIZE)
	{
		jndex = 0;
		while (jndex < 64)
		{
			color = (index + jndex) / (MEM_SIZE / vm_env->init.players.size) + 1;
			if (vm_env->arena.memory[index + jndex])
				attron(COLOR_PAIR(color));
			mvprintw(index / 64, jndex * 3, "%2.2x ",
						 vm_env->arena.memory[index + jndex]);
			attroff(COLOR_PAIR(color));
			jndex++;
		}
		index += 64;
	}
	ft_draw_processes(vm_env);
	refresh();
	//usleep(10000);
	getch();
	init = 1;
  //  endwin();
	return (0);
}
