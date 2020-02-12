/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:08:39 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 05:55:15 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_aff(t_vm_env *env, t_vm_process *process)
{
	int				reg_value;
	int				status;

	(void)env;
	reg_value = ft_get_memory(process, &process->operation.args[0], &status);
	if (!(env->init.flags & FLAG_visualizer))
		ft_printf("Aff: %c\n", (char)(reg_value % 256));
	return (SUCCESS);
}
