/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:08:39 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:47:54 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_exec_aff(t_vm_env *env, t_vm_process *process)
{
	int	status;

	(void)env;
	ft_putchar(ft_get_memory(process, &process->operation.args[0], &status));
	return (SUCCESS);
}
