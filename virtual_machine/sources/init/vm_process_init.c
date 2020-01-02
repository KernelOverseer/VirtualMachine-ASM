/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 20:57:03 by abiri             #+#    #+#             */
/*   Updated: 2020/01/01 20:57:04 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_vm_process *ft_new_vm_process(int player_id)
{
    static int      process_id;
    t_vm_process    *result;

    if (!(result = ft_memalloc(sizeof(t_vm_process))))
        return (NULL + ft_raise_exception(ERROR_allocation_problem, NULL));
    result->id = process_id++;
    result->carry = FALSE;
    result->registers[0] = player_id;
    return (result);
}