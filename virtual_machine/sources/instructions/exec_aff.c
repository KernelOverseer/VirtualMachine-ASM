/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_aff.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abiri <abiri@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/07 23:13:58 by abiri			 #+#	#+#			 */
/*   Updated: 2020/01/19 02:07:46 by abiri			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_aff(t_vm_env *env, t_vm_process *process)
{
	if (env->init.flags & FLAG_visualizer)
		return (SUCCESS);
	(void)env;
	ft_printf("PROCESS STATUS : =========================================\n");
	ft_printf("CARRY : %d\n", process->carry);
	ft_printf("REGISTERS:\n");
	for (int i = 0; i < REG_NUMBER; i++)
	{
		ft_printf("\tr%d : %d\n", i + 1, ft_int_endian(process->registers[i]));
	}
	ft_printf("==========================================================\n");
	return (SUCCESS);
}
