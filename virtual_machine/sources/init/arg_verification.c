/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 15:21:14 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 06:00:18 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flag_processing.h"
#include "virtual_machine.h"

const	t_flag_description	g_flags_data[] =
{
	{"dump", ft_set_memory_dump, FLAG_dump},
	{"v", ft_activate_flag_bit, FLAG_visualizer},
	{"n", ft_player_add_order, FLAG_player_number},
	{"s", ft_activate_flag_bit, FLAG_simple_visualiser},
	{"l", ft_activate_flag_bit, FLAG_live}
};

char	*ft_check_file_extension(char *filename, char *extension)
{
	char *ext;

	if (!filename)
		return (NULL);
	ext = ft_strrchr(filename, '.');
	if (ext == filename || !ext)
		return (NULL);
	if (ft_strequ(ext, extension))
		return (ext);
	return (NULL);
}

int		ft_activate_flag_bit(void *arg, int flag_index, char **params)
{
	t_vm_env	*vm_env;

	(void)params;
	vm_env = arg;
	vm_env->init.flags |= flag_index;
	return (1);
}

int		ft_process_flag(t_vm_env *vm_env, char *flag, char **args)
{
	int							index;
	const t_flag_description	*flag_data;

	index = 0;
	while (index < FLAG_COUNT)
	{
		flag_data = &g_flags_data[index];
		if (ft_strequ(flag, flag_data->flag_name))
			return (flag_data->handler(vm_env, flag_data->flag_index, args));
		index++;
	}
	return (ft_raise_exception(ERROR_wrong_flag, flag));
}

int		ft_check_args(t_vm_env *vm_env, int argc, char **argv)
{
	int	index;
	int	index_jump;

	index = 1;
	while (index < argc)
	{
		index_jump = 1;
		if (argv[index][0] == '-')
		{
			index_jump = ft_process_flag(vm_env, &argv[index][1],
					&argv[index + 1]);
			if (!index_jump)
				return (0);
		}
		else if (!ft_add_new_player(vm_env, argv[index]))
			return (0);
		index += index_jump;
	}
	return (1);
}
