/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser_draw_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 07:14:18 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 05:32:57 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		ft_visualiser_draw_border(void)
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

void		ft_visualiser_draw_info_border(void)
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

static int	ft_color_transform(char *color_array)
{
	int color;

	color = *color_array;
	if (color < 0)
	{
		color = -color;
		*color_array = color;
		attron(A_BOLD);
		attron(COLOR_PAIR(color));
	}
	else if (color == 0 && (color = 10))
		attron(COLOR_PAIR(10));
	else
		attron(COLOR_PAIR(color));
	return (color);
}

void		ft_visualiser_draw_winners(t_vm_env *env, t_vm_player *player)
{
	int c;

	(void)env;
	attron(COLOR_PAIR(9));
	attron(A_BOLD);
	ft_visualiser_draw_info_border();
	ft_visualiser_draw_border();
	mvprintw(BORDER_MARGINY + BORDER_PADDINGY + 2 + 5 + 50,
	BORDER_MARGINX + BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING,
	"Contestant %d,", player->index);
	mvprintw(BORDER_MARGINY + BORDER_PADDINGY + 2 + 5 + 50 + 2,
	BORDER_MARGINX + BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING,
	"\"%-*.*s\"", INFO_WIDTH - 6, INFO_WIDTH - 6, player->name);
	timeout(-1);
	c = 0;
	while (c != 'q')
		c = getch();
}

void		ft_visualiser_draw_memory(t_vm_env *env)
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
			color = ft_color_transform(&env->arena.colors[y * 64 + x]);
			mvprintw(BORDER_MARGINY + 1 + BORDER_PADDINGY + y,
				BORDER_MARGINX + 1 + BORDER_PADDINGX + x * 3,
				"%*.2x", 2 + !!(env->init.flags &
				FLAG_simple_visualiser), env->arena.memory[y * 64 + x]);
			if (color == RAW_CURSOR_MODE)
				env->arena.colors[y * 64 + x] = 0;
			attroff(A_BOLD);
			attroff(COLOR_PAIR(color));
			x++;
		}
		y++;
	}
}
