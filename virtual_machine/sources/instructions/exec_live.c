/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_live.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abiri <kerneloverseer@pm.me>			   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/07 23:14:18 by abiri			 #+#	#+#			 */
/*   Updated: 2020/01/07 23:14:19 by abiri			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_live(t_vm_env *env, t_vm_process *process)
{
	int player_code;

	ft_printf("live from process %d on position %d cycle %d\n", process->id + 1, process->current_position, env->settings.cycles_number);
	player_code = -process->operation.args[0].value.int4;
	process->is_live = 1;
	if (player_code > 0 || player_code <= env->init.players.size)
		env->settings.last_alive = player_code;
	//env->settings.last_alive = player_code;
	process->last_live_cycle = env->settings.cycles_number;
	env->settings.lives_in_cycle++;
	return (SUCCESS);
}
