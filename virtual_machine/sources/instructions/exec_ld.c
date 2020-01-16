/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:14:15 by abiri             #+#    #+#             */
/*   Updated: 2020/01/07 23:14:16 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_ld(t_vm_env *env, t_vm_process *process)
{
    int     status;
    t_intat value;

    value.int4 = 0;
    if (process->operation.args[0].type == IND_CODE)
    {
        process->operation.args[0].value.int4 = ft_int_endian
                (process->operation.args[0].value.int4);
        process->operation.args[0].value.int4 %= IDX_MOD;
    }
    if (!(process->operation.args[1].type == REG_CODE))
        return (ERROR);
    value.int4 = ft_get_memory(process, &process->operation.args[0], &status);
    if (!status)
        return (ERROR);
    if (!ft_set_memory(process, &process->operation.args[1], value))
        return (ERROR);
    if (process->operation.args[1].value.int1 == 1)
        process->carry = 1;
    else if (value.int4 != 0)
        process->carry = 0;
	return (SUCCESS);
}
