/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   process_execution.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abiri <abiri@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/02 17:00:45 by abiri			 #+#	#+#			 */
/*   Updated: 2020/01/17 11:06:05 by abiri			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "virtual_machine.h"

int ft_valid_opcode(int opcode)
{
	if (opcode > 0 && opcode <= OPERATION_COUNT)
		return (SUCCESS);
	return (ERROR);
}

unsigned int	ft_get_value(unsigned char *mem, int size)
{
	if (size == 1)
		return (*((unsigned char*)mem));
	else if (size == 2)
		return (ft_short_endian(*((unsigned short int *)mem)));
	else if (size == 4)
		return (ft_int_endian(*((unsigned int *)mem)));
	return (0);
}

/*int ft_debug_print_argument_no_encoding(t_op *operation, unsigned char *mem)
{
	int i;
	int offset;
	int t_ind_size;

	i = 0;
	offset = 0;
	t_ind_size = operation->label_size ? 2 : 4;
	while (i < operation->args_number)
	{
		if (operation->args_type[i] & T_DIR)
		{
			printf("%c%d ", DIRECT_CHAR, ft_get_value(mem + offset, t_ind_size));
			offset += t_ind_size;
		}
		else if (operation->args_type[i] & T_IND)
		{
			printf("%d ", ft_get_value(mem + offset, T_IND));
			offset += T_IND;
		}
		else if (operation->args_type[i] & T_REG)
		{
			printf("r%d ", ft_get_value(mem + offset, 1));
			offset += 1;
		}
		i++;
	}
	return (offset);
}

int ft_debug_print_argument_types(int arg_types, int arg_count, unsigned
char *mem, int t_ind_size)
{
	int i;
	int type;
	int offset;

	i = 0;
	offset = 0;
	while (i < arg_count) {
		type = arg_types >> (6 - i * 2);
		type &= 0b11;
		if (type == DIR_CODE)
		{
			printf("%c%d ", DIRECT_CHAR, ft_get_value(mem + offset, t_ind_size));
			offset += t_ind_size;
		}
		else if (type == IND_CODE)
		{
			printf("%d ", ft_get_value(mem + offset, T_IND));
			offset += T_IND;
		}
		else if (type == REG_CODE)
		{
			printf("r%d ", ft_get_value(mem + offset, 1));
			offset += 1;
		}
		i++;
	}
	return (offset);
}

int ft_debug_extract_operations(t_vm_process *process, t_vm_arena *arena)
{
	int opcode;
	int argument_types;
	t_op	*operation;
	int	 offset;

	opcode = arena->memory[process->current_position % MEM_SIZE];
	if (!ft_valid_opcode(opcode))
		return (ERROR);
	operation = &g_op_tab[opcode - 1];
	printf("%d:\t%s  ", process->id, operation->name);
	if (operation->octet_codage)
	{
		argument_types = arena->memory[process->current_position % MEM_SIZE +
									   1];
		offset = ft_debug_print_argument_types(argument_types,
											   operation->args_number,
											   &arena->memory[
													   process->current_position
													   % MEM_SIZE + 2],
													   operation->label_size ? 2 : 4);
		offset++;
	}
	else
	{
		offset = ft_debug_print_argument_no_encoding(operation, &arena->memory[
				process->current_position
				% MEM_SIZE + 1]);
	}
	printf("\n");
	return (offset);
}
*/

int	ft_get_arguments_types(t_vm_process *process, t_vm_arena *arena)
{
	t_op			*op_data;
	int				index;
	int				offset;
	int				current_error;
	unsigned char	type_byte;

	index = 0;
	current_error = 0;
	offset = 1;
	op_data = &g_op_tab[process->operation.op_code - 1];
	type_byte = arena->memory[ft_modulus(process->current_position +
		offset, MEM_SIZE)];
	while (index < op_data->args_number)
	{
		process->operation.args[index].type =
			(((type_byte >> (6 - 2 * index)) & 0b11));
		if (!(op_data->args_type[index] & (1 <<
			(process->operation.args[index].type - 1))))
			current_error = 1;
		if (process->operation.args[index].type == REG_CODE)
			offset += T_REG;
		else if (process->operation.args[index].type == IND_CODE)
			offset += IND_SIZE;
		else if (process->operation.args[index].type == DIR_CODE)
			offset += DIR_SIZE - (2 * op_data->label_size);
		index++;
	}
	process->operation.op_size = offset + 1;
	return (!current_error);
}

int	ft_load_arguments_types(t_vm_process *process)
{
	t_op	*op_data;
	int		index;

	index = 0;
	op_data = &g_op_tab[process->operation.op_code - 1];
	while (index < op_data->args_number)
	{
		process->operation.args[index].type = op_data->args_type[index];
		if (process->operation.args[index].type == REG_CODE)
			process->operation.op_size += T_REG;
		else if (process->operation.args[index].type == IND_CODE)
			process->operation.op_size += IND_SIZE;
		else if (process->operation.args[index].type == DIR_CODE)
			process->operation.op_size += DIR_SIZE - (2 * op_data->label_size);
		index++;
	}
	return (SUCCESS);
}

void	ft_get_mem_int(t_intat *value, char size, unsigned char *mem)
{
	if (size == 1)
		value->int1 = *((char *)mem);
	else if (size == 2)
		value->int2 = *((short int *)mem);
	else if (size == 4)
		value->int4 = *((int *)mem);
}

int	ft_check_arguments_errors(t_vm_argument *argument)
{
	if (argument->type == REG_CODE && (argument->value.int1 > REG_NUMBER
		|| argument->value.int1 < 1))
		return (0);
	return (1);
}

int	ft_load_arguments_value(t_vm_process *process, t_vm_arena *arena)
{
	t_op			*op_data;
	unsigned char	*mem;
	int				index;
	int				size;
	int				offset;
	int				result;

	index = 0;
	op_data = &g_op_tab[process->operation.op_code - 1];
	offset = (op_data->octet_codage ? 1 : 0) + 1;
	mem = &arena->memory[ft_modulus(process->current_position + offset,
		MEM_SIZE)];
	result = 1;
	size = 0;
	while (index < op_data->args_number)
	{
		if (process->operation.args[index].type == REG_CODE)
			size = T_REG;
		else if (process->operation.args[index].type == IND_CODE)
			size = IND_SIZE;
		else if (process->operation.args[index].type == DIR_CODE)
			size = DIR_SIZE - (2 * op_data->label_size);
		process->operation.args[index].value = ft_read_memory_address(arena,
			(process->current_position + offset) % MEM_SIZE,
			size);
		result &= ft_check_arguments_errors(&process->operation.args[index]);
		offset += size;
		mem += size;
		index++;
	}
	return (result);
}

int	ft_parse_operation_arguments(t_vm_process *process, t_vm_arena *arena)
{
	t_op	*op_data;

	op_data = &g_op_tab[process->operation.op_code - 1];
	process->operation.op_size = 1;
	if (op_data->octet_codage)
	{
		if (!ft_get_arguments_types(process, arena))
		{
			ft_printf("\t\tOCTET CODAGE IS WRONG\n");
			return (ERROR);
		}
	}
	else
	{
		if (!ft_load_arguments_types(process))
			return (ERROR);
	}
	if (!ft_load_arguments_value(process, arena))
	{
		ft_printf("\t\tARGUMENT VALUE ERROR\n");
		return (ERROR);
	}
	process->operation.op_data = op_data;
	return (SUCCESS);
}

int	ft_parse_operation(t_vm_process *process, t_vm_arena *arena)
{
	t_vm_operation	*operation;

	operation = &(process->operation);
	operation->op_code = arena->memory[ft_modulus(process->current_position, MEM_SIZE)];
	if (!ft_valid_opcode(operation->op_code))
	{
		// ft_printf("%*@OPCODE IS WRONG\n%@", cRED);
		return (ERROR);
	}
	// printf("OPCODE IS VALID\n");
	if (!ft_parse_operation_arguments(process, arena))
	{
		// ft_printf("%*@ARGUMENTS ARE WRONG\n%@", cRED);
		return (ERROR);
	}
	// printf("PARSED ARGUMENTS\n");
	return (SUCCESS);
}

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
			sprintf(buffer, "%d", operation.args[index].value.int2);
		else if (operation.args[index].type == DIR_CODE)
			sprintf(buffer, "%d", operation.args[index].value.int4);
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
	// printf("PARSING INSTRUCTION\n");

/*	if (!ft_parse_operation(process, arena))
		return (ERROR);*/

//	printf("EXECUTING OPERATION : %s at cycle : %ld\n", process->operation.op_data->name,
//			env->settings.cycles_number);
	//if (!(env->init.flags & (FLAG_visualizer | FLAG_dump)))
	if (process->operation.op_data || ft_get_arguments_types(process, arena))
	{
		process->operation.op_size = 1;
		ft_bzero(&process->operation.args, sizeof(process->operation.args));
		if (ft_parse_operation_arguments(process, arena))
			{
				debug_print_operation(process->operation, process->id + 1, process);
				process->operation.op_data->exec(env, process);
			}
			else
				ft_printf("re parsing operation results in error\n");
		//ft_get_arguments_types(process, arena);
		//ft_load_arguments_value(process, arena);
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
