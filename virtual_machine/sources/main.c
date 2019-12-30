/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:59:36 by abiri             #+#    #+#             */
/*   Updated: 2019/12/30 16:09:30 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_vm_env	vm_env;

	ft_bzero(&vm_env, sizeof(t_vm_env));
	if (!ft_check_args(&vm_env, argc, argv))
	{
		printf("argument error\n");
		return (-1);
	}
	return (0);
}
