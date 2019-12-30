/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:59:55 by abiri             #+#    #+#             */
/*   Updated: 2019/12/30 16:05:13 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE
# define VIRTUAL_MACHINE
# include "libft.h"

typedef struct	s_vm_init
{
	int			flags;
	int			next_player_index;
}				t_vm_init;

typedef struct	s_vm_env
{
	t_vm_init	init;
}				t_vm_env;

# include "flag_processing.h"
#endif
