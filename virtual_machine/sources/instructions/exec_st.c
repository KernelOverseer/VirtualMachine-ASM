/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_st.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abiri <kerneloverseer@pm.me>			   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/07 23:14:50 by abiri			 #+#	#+#			 */
/*   Updated: 2020/01/23 00:44:00 by abiri            ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_st(t_vm_env *env, t_vm_process *process)
{
	t_intat value;
	int		status;
	int		offset;

	status = SUCCESS;
	value.int4 = ft_get_memory(process, &process->operation.args[0], &status);
	if (!status)
		return (ERROR);
	if (process->operation.args[1].type == IND_CODE)
		process->operation.args[1].value.int2 %= IDX_MOD;
	if (!ft_set_memory(process, &process->operation.args[1], value))
		return (ERROR);
	return (SUCCESS);
}
