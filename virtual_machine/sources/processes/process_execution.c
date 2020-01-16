/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:00:45 by abiri             #+#    #+#             */
/*   Updated: 2020/01/06 02:55:52 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int ft_valid_opcode(int opcode)
{
    if (opcode > 0 && opcode < 18)
        return (SUCCESS);
    return (ERROR);
}

unsigned int    ft_get_value(unsigned char *mem, int size)
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
    t_op    *operation;
    int     offset;

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
	unsigned char	type_byte;

	index = 0;
	op_data = &g_op_tab[process->operation.op_code - 1];
	type_byte = arena->memory[(process->current_position +
		process->operation.op_size) % MEM_SIZE];
	while (index < op_data->args_number)
	{
		process->operation.args[index].type =
			(((type_byte >> (6 - 2 * index)) & 0b11));
		index++;
	}
	process->operation.op_size += 1;
	return (SUCCESS);
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

int	ft_load_arguments_value(t_vm_process *process, t_vm_arena *arena)
{
	t_op			*op_data;
	unsigned char	*mem;
	int				index;
	int				size;

	index = 0;
	op_data = &g_op_tab[process->operation.op_code - 1];
	mem = &arena->memory[(process->current_position + process->operation.op_size)
		% MEM_SIZE];
	while (index < op_data->args_number)
	{
		if (process->operation.args[index].type == REG_CODE)
			size = T_REG;
		else if (process->operation.args[index].type == IND_CODE)
			size = IND_SIZE;
		else if (process->operation.args[index].type == DIR_CODE)
            size = DIR_SIZE - (2 * op_data->label_size);
		ft_get_mem_int(&(process->operation.args[index].value),
				size, mem);
		mem += size;
		process->operation.op_size += size;
		index++;
	}
	return (SUCCESS);
}

int	ft_parse_operation_arguments(t_vm_process *process, t_vm_arena *arena)
{
	t_op	*op_data;

	op_data = &g_op_tab[process->operation.op_code - 1];
	process->operation.op_size = 1;
	if (op_data->octet_codage)
		ft_get_arguments_types(process, arena);
	else
		ft_load_arguments_types(process);
	ft_load_arguments_value(process, arena);
	process->operation.op_data = op_data;
	return (SUCCESS);
}

int	ft_parse_operation(t_vm_process *process, t_vm_arena *arena)
{
	t_vm_operation	*operation;

	operation = &(process->operation);
	operation->op_code = arena->memory[process->current_position % MEM_SIZE];
	if (!ft_valid_opcode(operation->op_code))
		return (ERROR);
	// printf("OPCODE IS VALID\n");
	ft_parse_operation_arguments(process, arena);
	// printf("PARSED ARGUMENTS\n");
	return (SUCCESS);
}

void ft_debug_print(char *str)
{
    static int fd = -1;

    if (fd == -1) {
        fd = open("/dev/ttys001", O_WRONLY);
    }
    ft_putstr_fd(str, fd);
}

void	debug_print_operation(t_vm_operation operation)
{
	t_op	*op_data;
	int		index;
	char    buffer[2048];

	op_data = &g_op_tab[operation.op_code - 1];
	sprintf(buffer, "\t%s ", op_data->name);
    ft_debug_print(buffer);
	index = 0;
	while (index < op_data->args_number)
	{
		if (operation.args[index].type == REG_CODE)
			sprintf(buffer, "r%d ", operation.args[index].value.int1);
		else if (operation.args[index].type == DIR_CODE && op_data->label_size)
			sprintf(buffer, "%%%d ", ft_short_endian(operation.args[index].value.int2));
		else if (operation.args[index].type == DIR_CODE)
			sprintf(buffer, "%%%d ", ft_int_endian(operation.args[index].value.int4));
		else if (operation.args[index].type == IND_CODE)
			sprintf(buffer, "%d ", ft_int_endian(operation.args[index].value.int4));
		index++;
        ft_debug_print(buffer);
        sprintf(buffer, "\n");
        ft_debug_print(buffer);
	}
}

int	ft_execute_instruction(t_vm_env *env, t_vm_process *process, t_vm_arena
*arena)
{
	// printf("PARSING INSTRUCTION\n");
	if (!ft_parse_operation(process, arena))
        return (ERROR);
	if (process->operation.op_data)
	    process->operation.op_data->exec(env, process);
	process->remaining_cycles = process->operation.op_data->cycle_number + 1;
	//debug_print_operation(process->operation);
    return (SUCCESS);
}
