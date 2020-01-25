/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 04:20:02 by abiri             #+#    #+#             */
/*   Updated: 2020/01/23 04:47:37 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int	ft_modulus(int value, int modulus)
{
	if (value < 0)
		return (modulus + value % modulus);
	else
		return (value % modulus);
}

int	ft_limit_address(int value)
{
	if (value < 0)
		return (-(-value % IDX_MOD));
	return (value % IDX_MOD);
}
