/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_lld.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abiri <abiri@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/07 23:14:19 by abiri			 #+#	#+#			 */
/*   Updated: 2020/01/19 06:12:01 by abiri			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_lld(t_vm_env *env, t_vm_process *process)
{
	int		status;
	t_intat	value;

	value.int4 = 0;
	if (!(process->operation.args[1].type == REG_CODE))
		return (ERROR);
	value.int4 = ft_get_memory(process, &process->operation.args[0], &status);
	if (!status)
		return (ERROR);
	if (!ft_set_memory(process, &process->operation.args[1], value))
		return (ERROR);
	if (!value.int4)
		process->carry = 1;
	else
		process->carry = 0;
	return (SUCCESS);
}
