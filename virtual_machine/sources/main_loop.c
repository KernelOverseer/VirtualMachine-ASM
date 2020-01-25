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

int ft_op_wait(t_vm_process *process, t_vm_arena *arena)
{
	int	opcode;

	opcode = arena->memory[ft_modulus(process->current_position, MEM_SIZE)];
	if (!ft_valid_opcode(opcode))
		return (0);
	//printf("WAITING FOR OPERATION: %s for %d cycles\n", g_op_tab[opcode - 1].name, g_op_tab[opcode - 1].cycle_number);
	return (g_op_tab[opcode - 1].cycle_number);
}

int ft_execute_processes(t_vm_env *env)
{
	t_vm_process	*process;
	int			 status;

	env->arena.processes.iterator = env->arena.processes.first;
	while ((process = ttslist_iter_content(&(env->arena.processes))))
	{
		process->current_position = ft_modulus(process->current_position, MEM_SIZE);
		if (process->born_cycle == env->settings.cycles_number)
			continue ;
		if (process->current_position != process->last_position)
		{
			process->last_position = process->current_position;
			process->remaining_cycles = ft_op_wait(process, &env->arena) - 1;
			if (env->settings.cycles_number == 1)
				process->remaining_cycles += 1;
		}
		if (process->remaining_cycles <= 0)
		{
			ft_execute_instruction(env, process, &env->arena);
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
				ft_dump_memory(env);
			return (ERROR);
		}
	}
	else if (env->init.flags & FLAG_visualizer)
		ft_visualizer_init(env);
	else
		ft_printf("It is now cycle %ld\n", env->settings.cycles_number);
	if (env->arena.processes.size == 0)
		return (ERROR);
	return (SUCCESS);
}

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
	t_list_node	 *node;
	t_vm_process	*process;

	env->arena.processes.iterator = env->arena.processes.first;
	while ((node = ttslist_iter(&env->arena.processes)))
	{
		process = node->content;
		if (env->settings.cycles_to_die <= 0 || process->last_live_cycle +
			env->settings.cycles_to_die < env->settings.cycles_number)
			ttslist_splice(&env->arena.processes, node);
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
			if (env->settings.lives_in_cycle >= NBR_LIVE ||
				env->settings.number_of_checks_from_last_change >= MAX_CHECKS)
			{
				env->settings.cycles_to_die -= CYCLE_DELTA;
				env->settings.number_of_checks_from_last_change = 0;
			}
			env->settings.last_period_cycles = 0;
		}
		if (!ft_execute_processes(env))
			return (SUCCESS);
		env->settings.last_period_cycles++;
		env->settings.cycles_number++;
	}
}
