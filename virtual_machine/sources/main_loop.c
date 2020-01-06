/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:27:47 by abiri             #+#    #+#             */
/*   Updated: 2020/01/02 16:27:47 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

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
    t_vm_process *process;

    env->arena.processes.iterator = env->arena.processes.first;
    while ((process = ttslist_iter_content(&(env->arena.processes))))
    {
        ft_execute_instruction(process, &env->arena);
        process->current_position++;
        if (process->remaining_cycles > 0)
            process->remaining_cycles--;
    }
    return (SUCCESS);
}

int ft_main_vm_loop(t_vm_env *env)
{
    while (TRUE)
    {
        if (env->settings.cycles_number && env->settings.cycles_number %
            env->settings.cycles_to_die == 0)
        {
            if (ft_no_lives_from_processes(&env->arena.processes, env))
                break;
        }
        ft_execute_processes(env);
        if (env->init.flags & FLAG_visualizer)
            ft_visualizer_init(env);
        env->settings.cycles_number++;
    }
    return (SUCCESS);
}