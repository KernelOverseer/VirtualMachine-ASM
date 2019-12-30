/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 15:21:14 by abiri             #+#    #+#             */
/*   Updated: 2019/12/30 16:12:27 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

const	t_flag_description	g_flags_data[] =
{
	{"dump", ft_activate_flag_bit, flag_dump}
//	{"n", ft_player_order_set, flag_player_number}
};

int	ft_activate_flag_bit(void *arg, int flag_index, char *param)
{
	t_vm_env	*vm_env;

	(void)param;
	vm_env = arg;
	vm_env->init.flags |= (1 << flag_index);
	return (1);
}

int	ft_process_flag(t_vm_env *vm_env, char *flag, char *param)
{
	int							index;
	const t_flag_description	*flag_data;

	index = 0;
	while (index < FLAG_COUNT)
	{
		flag_data = &g_flags_data[index];
		if (ft_strequ(flag, flag_data->flag_name))
			return (flag_data->handler(vm_env, flag_data->flag_index, param));
		index++;
	}
	return (0);
}

int	ft_check_args(t_vm_env *vm_env, int argc, char **argv)
{
	int	index;

	index = 1;
	while (index < argc)
	{
		if (argv[index][0] == '-')
		{
			if (!ft_process_flag(vm_env, argv[index] + 1, argv[index + 1]))
				return (0);
		}
//		else
//			ft_process_player();
		else
			return (0);
		index++;
	}
	return (1);
}
