/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 23:13:58 by abiri             #+#    #+#             */
/*   Updated: 2020/01/07 23:14:10 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_aff(t_vm_env *env, t_vm_process *process)
{
    (void)env;
    printf("PROCESS STATUS : =========================================\n");
    printf("CARRY : %d\n", process->carry);
    printf("REGISTERS:\n");
    for (int i = 0; i < REG_NUMBER; i++)
    {
        printf("\tr%d : %d\n", i + 1, process->registers[i]);
    }
    printf("==========================================================\n");
	return (SUCCESS);
}
