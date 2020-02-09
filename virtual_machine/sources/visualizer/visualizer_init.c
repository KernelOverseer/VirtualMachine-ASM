/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:21:16 by abiri             #+#    #+#             */
/*   Updated: 2020/02/09 09:22:44 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#define BORDER_PADDINGY 2
#define BORDER_PADDINGX 4
#define BORDER_MARGINY 2
#define BORDER_MARGINX 4
#define INFO_PADDING 2
#define INFO_WIDTH 40
#define TEXT_SPEED 1

void	ft_visualiser_draw_border(void)
{
	int x;

	x = 0;
	attron(A_REVERSE);
	while (x < 192 + BORDER_PADDINGX * 2 + 2)
	{
		mvprintw(BORDER_MARGINY, BORDER_MARGINX + x, " ");
		mvprintw(BORDER_MARGINY + BORDER_PADDINGY * 2 + 64 + 1,
			BORDER_MARGINX + x, " ");
		x++;
	}
	x = 0;
	while (x < 64 + BORDER_PADDINGY * 2 + 2)
	{
		mvprintw(BORDER_MARGINY + x, BORDER_MARGINX, " ");
		mvprintw(BORDER_MARGINY + x,
			BORDER_MARGINX + BORDER_PADDINGX * 2 + 192 + 1, " ");
		x++;
	}
	attroff(A_REVERSE);
}

void	ft_visualiser_draw_info_border(void)
{
	int x;

	x = 0;
	attron(A_REVERSE);
	while (x < INFO_WIDTH)
	{
		mvprintw(BORDER_MARGINY, BORDER_MARGINX +
			BORDER_PADDINGX * 2 + 192 + 2 + x, " ");
		mvprintw(BORDER_MARGINY + BORDER_PADDINGY * 2 + 64 + 1,
			BORDER_MARGINX + BORDER_PADDINGX * 2 + 192 + 2 + x, " ");
		x++;
	}
	x = 0;
	while (x < 64 + BORDER_PADDINGY * 2 + 2)
	{
		mvprintw(BORDER_MARGINY + x,
			BORDER_MARGINX + BORDER_PADDINGX * 2 + 192 + 1 + INFO_WIDTH, " ");
		x++;
	}	
	attroff(A_REVERSE);
}

void	ft_visualiser_draw_memory(t_vm_env *env)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	ft_visualiser_draw_border();
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			color = env->arena.colors[y * 64 + x];
			if (color < 0)
			{
				color = -color;
				env->arena.colors[y * 64 + x] = color;
				attron(A_BOLD);
				attron(COLOR_PAIR(color));
			}
			else if (color == 0 && (color = 10))
				attron(COLOR_PAIR(10));
			else
				attron(COLOR_PAIR(color));
			mvprintw(BORDER_MARGINY + 1 + BORDER_PADDINGY + y, BORDER_MARGINX + 1 +
				BORDER_PADDINGX + x * 3, "%*.2x", 2 + !!(env->init.flags & FLAG_simple_visualiser), env->arena.memory[y * 64 + x]);
			if (color > MAX_PLAYERS && color != 10)
				env->arena.colors[y * 64 + x] = color - MAX_PLAYERS;
			attroff(A_BOLD);
			attroff(COLOR_PAIR(color));
			x++;
		}
		y++;
	}
}

void ft_init_visualiser(t_vm_env *env)
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
	}
	else
	{
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_BLUE, COLOR_BLACK);
		init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		init_pair(5, COLOR_RED, COLOR_WHITE);
		init_pair(6, COLOR_BLUE, COLOR_WHITE);
		init_pair(7, COLOR_MAGENTA, COLOR_WHITE);
		init_pair(8, COLOR_YELLOW, COLOR_WHITE);
		init_pair(9, COLOR_GREEN, COLOR_BLACK);
		init_pair(10, COLOR_WHITE, COLOR_BLACK);
	}
	ft_visualiser_draw_memory(env);
}

void	ft_visualiser_update_value(t_vm_env *env, int offset, int color, int size)
{
	int	index;

	if (env->init.cycle_skip <= 0)
		env->init.cycle_skip = 1;
	if (!(env->init.flags & FLAG_visualizer))
		return ;
	if (env->settings.cycles_number % env->init.cycle_skip && color > MAX_PLAYERS)
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

char	*ft_adjust_string(char *string, int padding, int len)
{
	if (len > padding)
		return (string + ((int)(time(0) * TEXT_SPEED) % (len - padding + 1)));
	return (string);
}

void	ft_visualiser_print_player_state(t_vm_env *env, t_vm_player *player, int y_pos)
{
	int		xoff;

	xoff = BORDER_MARGINX + BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING;
	if (env->settings.last_alive == player->index)
		attron(COLOR_PAIR(9));
	mvprintw(y_pos, xoff, "Player %1.1d : %*.*-s", player->index,
		(INFO_WIDTH - INFO_PADDING * 2) - 11,
		(INFO_WIDTH - INFO_PADDING * 2) - 11, ft_adjust_string(player->name,
		(INFO_WIDTH - INFO_PADDING * 2) - 11, ft_strlen(player->name)));
	y_pos += 1;
	mvprintw(y_pos, xoff, "   Last live : %*-d",
	(INFO_WIDTH - INFO_PADDING * 2) - 15, player->last_live);
	// mvprintw(y_pos + 2, xoff, "Player %1.1d : %*.*-s", player->index,
	// 	(INFO_WIDTH - INFO_PADDING * 2) - 11,
	// 	(INFO_WIDTH - INFO_PADDING * 2) - 11, &player->name[text_off]);
	attroff(COLOR_PAIR(9));
}

void	ft_visualiser_draw_info(t_vm_env *env)
{
	int			offset;
	int			padding;
	t_vm_player	*player;

	offset = BORDER_MARGINY + BORDER_PADDINGY;
	ft_visualiser_draw_info_border();
	mvprintw(offset, BORDER_MARGINX +
		BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING,
		"%*s", (INFO_WIDTH - INFO_PADDING * 2) - 2 - 6,
		(env->init.visu_stop < 0) ? "_>  PAUSE  <_" : "-> RUNNING <-");
	offset += 2;
	padding = (INFO_WIDTH - INFO_PADDING * 2) / 2 - 1;
	mvprintw(offset, BORDER_MARGINX +
		BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING,
		"%*.*-s : %*d", padding - 3, padding - 3, "Speed", padding,
		env->init.cycle_skip);
	offset += 2;
	mvprintw(offset, BORDER_MARGINX +
		BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING,
		"%*.*-s : %*d", padding - 3, padding - 3, "Cycles", padding,
		env->settings.cycles_number);
	offset += 2;
	mvprintw(offset, BORDER_MARGINX +
		BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING,
		"%*.*-s : %*zu", padding - 3, padding - 3, "Processes", padding,
		env->arena.processes.size);
	offset += 2;
	mvprintw(offset, BORDER_MARGINX +
		BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING, "%*.*-s : %*ld",
		padding - 3, padding - 3, ft_adjust_string("CYCLES_TO_DIE",
		padding - 3, 13), padding, env->settings.cycles_to_die);
	offset += 5;
	env->init.players.iterator = env->init.players.first;
	while ((player = ttslist_iter_content(&env->init.players)))
	{
		ft_visualiser_print_player_state(env, player, offset);
		offset += 3;
	}
}

int		ft_stop_loop(t_vm_env *env)
{
	int	 c;

	if (env->init.visu_stop >= 0)
		return (getch());
	c = 0;
	while (c != ' ')
		c = getch();
	return (c);
}

void	ft_visualiser_handle_keys(t_vm_env *env)
{
	int c;

	//c = ft_stop_loop(env);
	c = 0;
	while (c != ' ' && c != 's')
	{
		c = getch();
		if (c == KEY_LEFT)
			env->init.cycle_skip -= 5;
		else if (c == KEY_RIGHT)
			env->init.cycle_skip += 5;
		else if (c == KEY_UP)
			env->init.cycle_skip += 50;
		else if (c == KEY_DOWN)
			env->init.cycle_skip -= 50;
		else if (c == ' ')
			env->init.visu_stop = -env->init.visu_stop;
		else if (c == 's')
			env->init.cycle_skip = 1;
		if (env->init.cycle_skip < 0)
			env->init.cycle_skip = 1;
		ft_visualiser_draw_info(env);
		if (env->init.visu_stop >= 0)
			break ;
	}
	timeout(env->init.visu_stop);
}

void	ft_visualiser_draw(t_vm_env *env)
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
	//refresh();
}