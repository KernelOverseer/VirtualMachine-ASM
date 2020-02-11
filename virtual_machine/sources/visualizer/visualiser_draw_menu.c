/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser_draw_menu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 07:16:39 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 21:57:15 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void	ft_write_field(int *offset, int padding,
	char *name, int value)
{
	mvprintw(*offset, BORDER_MARGINX +
		BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING,
		"%*.*-s : %*d", padding - 3, padding - 3, name, padding,
		value);
	*offset += 2;
}

char		*ft_adjust_string(char *string, int padding, int len)
{
	if (len > padding)
		return (string + ((int)(time(0) * TEXT_SPEED) % (len - padding + 1)));
	return (string);
}

void		ft_visualiser_print_player_state(t_vm_env *env,
	t_vm_player *player, int *y_pos)
{
	int		xoff;

	xoff = BORDER_MARGINX + BORDER_PADDINGX * 2 + 192 + 2 + INFO_PADDING;
	if (env->settings.last_alive == player->index)
		attron(COLOR_PAIR(9));
	mvprintw(*y_pos, xoff, "Player %1.1d : %*.*-s", player->index,
		(INFO_WIDTH - INFO_PADDING * 2) - 11,
		(INFO_WIDTH - INFO_PADDING * 2) - 11, ft_adjust_string(player->name,
		(INFO_WIDTH - INFO_PADDING * 2) - 11, ft_strlen(player->name)));
	*y_pos += 1;
	mvprintw(*y_pos, xoff, "   Last live : %*-d",
	(INFO_WIDTH - INFO_PADDING * 2) - 15, player->last_live);
	*y_pos += 2;
	attroff(COLOR_PAIR(9));
}

void		ft_visualiser_draw_info(t_vm_env *env)
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
	ft_write_field(&offset, padding, "Speed", env->init.cycle_skip);
	ft_write_field(&offset, padding, "Cycles", env->settings.cycles_number);
	ft_write_field(&offset, padding, "Processes", env->arena.processes.size);
	ft_write_field(&offset, padding, "Cycles to die",
		env->settings.cycles_to_die);
	offset += 5;
	env->init.players.iterator = env->init.players.first;
	while ((player = ttslist_iter_content(&env->init.players)))
		ft_visualiser_print_player_state(env, player, &offset);
}
