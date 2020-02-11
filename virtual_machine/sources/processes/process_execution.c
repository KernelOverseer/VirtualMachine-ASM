/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:47:25 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 06:04:18 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void ft_debug_print(char *str)
{
	static int fd = 1;

	if (fd == -1) {
		fd = open("/dev/ttys001", O_WRONLY);
	}
	ft_putstr_fd(str, fd);
}

void	debug_print_operation(t_vm_operation operation, int id, t_vm_process *process)
{
	t_op	*op_data;
	int		index;
	char	buffer[2048];

	op_data = &g_op_tab[operation.op_code - 1];
	sprintf(buffer, "P %4d | %s ", id, op_data->name);
	ft_debug_print(buffer);
	index = 0;
	while (index < op_data->args_number)
	{
		if (operation.args[index].type == REG_CODE)
			sprintf(buffer, "r%d", operation.args[index].value.int1);
		else if (operation.args[index].type == DIR_CODE && op_data->label_size)
			sprintf(buffer, "%%%d", operation.args[index].value.int2);
		else if (operation.args[index].type == DIR_CODE)
			sprintf(buffer, "%%%d", operation.args[index].value.int4);
		else if (operation.args[index].type == IND_CODE)
			sprintf(buffer, "%d", operation.args[index].value.int2);
		ft_debug_print(buffer);
		if (index < op_data->args_number - 1)
			ft_printf(" ");
		index++;
	}
	if (operation.op_code == 9 && process->carry)
	{
		sprintf(buffer, " OK");
		ft_debug_print(buffer);
	}
	else if (operation.op_code == 9)
	{
		sprintf(buffer, " FAILED");
		ft_debug_print(buffer);
	}
	else if (operation.op_code == 12)
	{
		sprintf(buffer, " (%d)", ft_modulus((operation.args[0].value.int4 % IDX_MOD) + process->current_position, MEM_SIZE));
		ft_debug_print(buffer);
	}
	sprintf(buffer, "\n");
	ft_debug_print(buffer);
}

int	ft_execute_instruction(t_vm_env *env, t_vm_process *process, t_vm_arena
	*arena)
{
	if (process->operation.op_data ||
		(ft_valid_opcode(process->operation.op_code) &&
			ft_get_arguments_types(process, arena)))
	{
		process->operation.op_size = 1;
		ft_bzero(&process->operation.args, sizeof(process->operation.args));
		if (ft_parse_operation_arguments(process, arena))
		{
			if (env->init.flags & FLAG_verbose)
				debug_print_operation(process->operation,
					process->id + 1, process);
			process->operation.op_data->exec(env, process);
		}
	}
	else
	{
		process->operation.op_code = arena->memory[process->current_position];
		if (ft_valid_opcode(process->operation.op_code))
			ft_get_arguments_types(process, arena);
		else
			process->operation.op_size = 1;
	}
	ft_bzero(&process->operation.args, sizeof(t_vm_argument) * 4);
	process->operation.op_data = NULL;
	return (SUCCESS);
}
