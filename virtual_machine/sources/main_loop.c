/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:14:14 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 21:58:45 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_no_lives_from_processes(t_list_head *processes, t_vm_env *env)
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

int	ft_op_wait(t_vm_env *env, t_vm_process *process, int newborn)
{
	int	opcode;

	opcode = env->arena.memory[ft_modulus(process->current_position, MEM_SIZE)];
	process->last_position = process->current_position;
	process->operation.op_size = 1;
	if (!ft_valid_opcode(opcode))
	{
		ft_visualiser_unhighlight_process(env, process);
		if (!newborn)
			process->current_position += 1;
		ft_visualiser_highlight_process(env, process);
		return (0);
	}
	if (!ft_parse_operation(process, &env->arena))
		process->operation.op_data = NULL;
	return (g_op_tab[opcode - 1].cycle_number);
}

int	ft_execute_processes(t_vm_env *env)
{
	t_vm_process	*process;

	env->arena.processes.iterator = env->arena.processes.first;
	while ((process = ttslist_iter_content(&env->arena.processes)))
	{
		process->current_position = ft_modulus(process->current_position,
			MEM_SIZE);
		ft_visualiser_highlight_process(env, process);
		if (process->current_position != process->last_position)
			process->remaining_cycles = ft_op_wait(env, process, 0) - 1;
		else if (process->remaining_cycles <= 0)
		{
			ft_execute_instruction(env, process, &env->arena);
			process->last_position = -1;
			ft_visualiser_unhighlight_process(env, process);
			process->current_position += process->operation.op_size;
			ft_visualiser_highlight_process(env, process);
			process->operation.op_size = 1;
		}
		process->remaining_cycles--;
	}
	ft_visualiser_draw(env);
	if (env->arena.processes.size == 0 || ft_dump_memory(env))
		return (ERROR);
	return (SUCCESS);
}

int	ft_remove_dead_processes(t_vm_env *env)
{
	t_list_node		*node;
	t_list_node		*next_node;
	t_vm_process	*process;

	node = env->arena.processes.first;
	while (node)
	{
		next_node = node->next;
		process = node->content;
		if (env->settings.cycles_to_die <= 0 || !process->is_live)
		{
			ttslist_splice(&env->arena.processes, node);
			free(process);
		}
		else
			process->is_live = 0;
		node = next_node;
	}
	return (SUCCESS);
}

int	ft_main_vm_loop(t_vm_env *env)
{
	ft_init_game(env);
	while (TRUE)
	{
		if (env->settings.last_period_cycles >= env->settings.cycles_to_die)
		{
			ft_remove_dead_processes(env);
			env->settings.number_of_checks++;
			env->settings.number_of_checks_from_last_change++;
			if (env->settings.lives_in_cycle >= NBR_LIVE ||
				env->settings.number_of_checks_from_last_change >= MAX_CHECKS)
			{
				env->settings.cycles_to_die -= CYCLE_DELTA;
				env->settings.number_of_checks_from_last_change = 0;
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
