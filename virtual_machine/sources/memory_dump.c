/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 04:57:05 by abiri             #+#    #+#             */
/*   Updated: 2020/01/23 05:28:32 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_set_memory_dump(void *arg, int flag_index, char **params)
{
	t_vm_env	*env;
	int			cycle_number;

	env = arg;
	if (!params[0])
		return (ft_raise_exception(ERROR_wrong_argument, ", try : --dump [cycle_number]"));
	if (!ft_parse_int(params[0], &cycle_number))
		return (ft_raise_exception(ERROR_wrong_argument, ", [cycle_number] should be an integer"));
	env->init.flags |= FLAG_dump;
	env->init.dump_cycle = cycle_number;
	return (2);
}

int	ft_dump_memory(t_vm_env *env)
{
	int	index;
	int	jndex;

	index = 0;
	while (index < (MEM_SIZE / 64))
	{
		jndex = 0;
		ft_printf("0x%4.4x : ", index * 64);
		while (jndex < 64)
		{
			ft_printf("%2.2x ", env->arena.memory[index * 64 + jndex]);
			jndex++;
		}
		ft_printf("\n");
		index++;
	}
	return (SUCCESS);
}
