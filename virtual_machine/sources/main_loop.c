/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:27:47 by abiri             #+#    #+#             */
/*   Updated: 2020/01/06 02:45:57 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include <stdarg.h>

int ft_no_lives_from_processes(t_list_head *processes, t_vm_env *env)
{
    t_vm_process    *process;

    processes->iterator = processes->first;
    while ((process = ttslist_iter_content(processes)))
    {
        if (env->settings.cycles_number - process->last_live_cycle >
        env->settings.cycles_to_die)
            return (!ERROR);
    }
    return (!SUCCESS);
}

int ft_execute_processes(t_vm_env *env)
{
    t_vm_process    *process;
    int             status;

    env->arena.processes.iterator = env->arena.processes.first;
    while ((process = ttslist_iter_content(&(env->arena.processes))))
    {
        if (process->remaining_cycles <= 0)
        {
            ft_execute_instruction(env, process, &env->arena);
            process->current_position += process->operation.op_size;
            process->operation.op_size = 1;
        }
        if (process->remaining_cycles > 0)
            process->remaining_cycles--;
    }
    if (env->arena.processes.size == 0)
        return (ERROR);
    return (SUCCESS);
}

void ft_init_game(t_vm_env *env)
{
    env->settings.last_alive = env->init.players.size;
    env->settings.last_period_cycles = 0;
    env->settings.cycles_number = 0;
    env->settings.lives_in_cycle = 0;
    env->settings.cycles_to_die = CYCLE_TO_DIE;
    env->settings.number_of_checks = 0;
    env->settings.number_of_checks_from_last_change = 0;
}

int ft_remove_dead_processes(t_vm_env *env)
{
    t_list_node     *node;
    t_vm_process    *process;

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
        if (env->init.flags & FLAG_visualizer)
            ft_visualizer_init(env);
        if (!ft_execute_processes(env))
            return (SUCCESS);
        env->settings.last_period_cycles++;
        env->settings.cycles_number++;
    }
}