/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main_loop.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abiri <abiri@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/02 16:27:47 by abiri			 #+#	#+#			 */
/*   Updated: 2020/01/23 02:26:01 by abiri			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "virtual_machine.h"
#include <stdarg.h>

int ft_no_lives_from_processes(t_list_head *processes, t_vm_env *env)
{
	t_vm_process	*process;

	processes->iterator = processes->first;
	while ((process = ttslist_iter_content(processes)))
	{
		if (env->settings.cycles_number - process->last_live_cycle >
		env->settings.cycles_to_die)
			return (!ERROR);
	}
	return (!SUCCESS);
}

int ft_op_wait(t_vm_process *process, t_vm_arena *arena, int newborn)
{
	int	opcode;

	opcode = arena->memory[ft_modulus(process->current_position, MEM_SIZE)];
	process->last_position = process->current_position;
	process->operation.op_size = 1;
	if (!ft_valid_opcode(opcode))
	{
		ft_printf("%d | opcode %d invalid\n", process->id + 1, opcode);
		if (!newborn)
			process->current_position += 1;
		return (0);
	}
//	ft_printf("process %d | is on %d\n", process->id + 1, opcode);
	if (!ft_parse_operation(process, arena))
	{
		process->operation.op_data = NULL;
		ft_printf("%d | wrong operation %d\n", process->id + 1, process->operation.op_code);
		//return (1);
	}
	else
		ft_printf("instruction is : %d\n", process->operation.op_code);
	//printf("WAITING FOR OPERATION: %s for %d cycles\n", g_op_tab[opcode - 1].name, g_op_tab[opcode - 1].cycle_number);
	return (g_op_tab[opcode - 1].cycle_number);
}

/*
**	CHANGE THE WAY YOU SKIP THE ERRORS IN INSTRUCTIONS
*/

int	ft_execute_processes(t_vm_env	*env)
{
	t_vm_process	*process;

	if (!(env->init.flags & FLAG_visualizer))
		ft_printf("It is now cycle %d\n", env->settings.cycles_number);
	env->arena.processes.iterator = env->arena.processes.first;
	while ((process = ttslist_iter_content(&env->arena.processes)))
	{
		process->current_position = ft_modulus(process->current_position, MEM_SIZE);
		if (process->id == 1)
			ft_printf("process %d | on %d waiting for %d\n", process->id + 1, process->current_position, process->remaining_cycles);
		if (process->current_position != process->last_position)
		{
			if (process->id == 1)
				ft_printf("process %5d | is parsing instruction\n", process->id + 1);
			process->remaining_cycles = ft_op_wait(process, &env->arena, 0) - 1;
		}
		else if (process->remaining_cycles <= 0)
		{
			ft_execute_instruction(env, process, &env->arena);
			if (process->operation.op_code != 9)
			{
				 ft_printf("ADV %d (%#4.4p -> %#4.4p) ", process->operation.op_size, process->current_position, process->current_position + process->operation.op_size);
				 for (int i = 0; i < process->operation.op_size; i++)
				 {
					if (i < process->operation.op_size - 1)
						ft_printf("%2.2x ", process->arena->memory[process->current_position + i]);
					else
						ft_printf("%2.2x", process->arena->memory[process->current_position + i]);
				 }
				ft_printf("\n");
			}
			process->last_position = -1;
			process->current_position += process->operation.op_size;
			process->operation.op_size = 1;
		}
		process->remaining_cycles--;
	}
	if (env->init.flags & FLAG_dump)
	{
		if (env->init.dump_cycle == env->settings.cycles_number)
		{
			if (env->init.flags & FLAG_visualizer)
			{
				ft_visualizer_init(env);
				sleep(1000);
			}
			else
			{
				ft_dump_memory(env);
				return (ERROR);
			}
		}
	}
	else if (env->init.flags & FLAG_visualizer)
		ft_visualizer_init(env);
	if (env->arena.processes.size == 0)
		return (ERROR);
	return (SUCCESS);
}

/*int ft_execute_processes(t_vm_env *env)
{
	t_vm_process	*process;
	int			 status;

	if (!(env->init.flags & FLAG_visualizer))
		ft_printf("It is now cycle %ld with processes %zu\n", env->settings.cycles_number, env->arena.processes.size);
	env->arena.processes.iterator = env->arena.processes.first;
	while ((process = ttslist_iter_content(&(env->arena.processes))))
	{
		ft_printf("executing process: %d still waiting for %d\n", process->id + 1, process->remaining_cycles);
		process->current_position = ft_modulus(process->current_position, MEM_SIZE);
		if (process->born_cycle == env->settings.cycles_number)
			continue ;
		if (process->current_position != process->last_position)
			process->remaining_cycles = ft_op_wait(process, &env->arena) - 1;
		if (process->remaining_cycles <= 0)
		{
		    ft_execute_instruction(env, process, &env->arena);
		    ft_printf("ADV %d (%#4.4x -> %#4.4x) ", process->operation.op_size, process->current_position, process->current_position + process->operation.op_size);
		    for (int i = 0;i < process->operation.op_size; i++)
		        ft_printf("%2.2x ", process->arena->memory[process->current_position + i]);
		    ft_printf("\n");
		    process->current_position += process->operation.op_size;
    		process->operation.op_size = 1;
		}
		process->remaining_cycles--;
	}
	if (env->init.flags & FLAG_dump)
	{
		if (env->init.dump_cycle == env->settings.cycles_number)
		{
			if (env->init.flags & FLAG_visualizer)
			{
				ft_visualizer_init(env);
				sleep(1000);
			}
			else
			{
				ft_dump_memory(env);
				return (ERROR);
			}
		}
	}
	else if (env->init.flags & FLAG_visualizer)
		ft_visualizer_init(env);
	if (env->arena.processes.size == 0)
		return (ERROR);
	return (SUCCESS);
}*/

void ft_init_game(t_vm_env *env)
{
	env->settings.last_alive = env->init.players.size;
	env->settings.last_period_cycles = 0;
	env->settings.cycles_number = 1;
	env->settings.lives_in_cycle = 0;
	env->settings.cycles_to_die = CYCLE_TO_DIE;
	env->settings.number_of_checks = 0;
	env->settings.number_of_checks_from_last_change = 0;
}

int ft_remove_dead_processes(t_vm_env *env)
{
	t_list_node		*node;
	t_list_node		*next_node;
	t_vm_process	*process;

	node = env->arena.processes.first;
	//ft_printf("doing a process check\n");
	while (node)
	{
		next_node = node->next;
		process = node->content;
//		ft_printf("verifying process (CTD) %d in cycle %d\n", process->id + 1, env->settings.cycles_number);
	//	ft_printf("(CTD %d) process 19 lived %d cycle is %d\n", env->settings.cycles_to_die, (env->settings.cycles_number - process->last_live_cycle - 1), env->settings.cycles_number);
		if (env->settings.cycles_to_die <= 0 || !process->is_live)
		{
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", process->id + 1, env->settings.cycles_number - process->last_live_cycle - 1, env->settings.cycles_to_die);
			ttslist_splice(&env->arena.processes, node);
		}
		else
			process->is_live = 0;
		node = next_node;
	}
	return (SUCCESS);
}

int ft_main_vm_loop(t_vm_env *env)
{
	ft_init_game(env);
	while (TRUE)
	{
		if (env->settings.last_period_cycles >= env->settings.cycles_to_die)
		{
			// HERE DO A CHECK
			ft_remove_dead_processes(env);
			env->settings.number_of_checks++;
			env->settings.number_of_checks_from_last_change++;
			ft_printf("lives in cycle is : %d\n", env->settings.lives_in_cycle);
			if (env->settings.lives_in_cycle >= NBR_LIVE ||
				env->settings.number_of_checks_from_last_change >= MAX_CHECKS)
			{
				env->settings.cycles_to_die -= CYCLE_DELTA;
				env->settings.number_of_checks_from_last_change = 0;
				ft_printf("Cycle to die is now %d\n", env->settings.cycles_to_die);
			}
			env->settings.lives_in_cycle = 0;
			env->settings.last_period_cycles = 0;
		}
		if (!ft_execute_processes(env))
			return (SUCCESS);
		env->settings.last_period_cycles++;
		env->settings.cycles_number++;
	}
}
