/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 05:36:56 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/24 05:46:34 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static void			ft_color(char *color)
{
	if (!ft_strcmp(color, "red"))
		ft_putstr("\e[1;31m");
	else if (!ft_strcmp(color, "green"))
		ft_putstr("\e[1;32m");
	else if (!ft_strcmp(color, "yellow"))
		ft_putstr("\e[1;33m");
	else if (!ft_strcmp(color, "blue"))
		ft_putstr("\e[1;34m");
	else if (!ft_strcmp(color, "magenta"))
		ft_putstr("\e[1;35m");
	else if (!ft_strcmp(color, "cyan"))
		ft_putstr("\e[1;36m");
	else if (!ft_strcmp(color, "RED"))
		ft_putstr("\e[1;41m");
	else if (!ft_strcmp(color, "GREEN"))
		ft_putstr("\e[1;42m");
	else if (!ft_strcmp(color, "YELLOW"))
		ft_putstr("\e[1;43m");
	else if (!ft_strcmp(color, "BLUE"))
		ft_putstr("\e[1;44m");
	else if (!ft_strcmp(color, "CYAN"))
		ft_putstr("\e[1;46m");
	else if (!ft_strcmp(color, "end") || !ft_strcmp(color, "END"))
		ft_putstr("\e[0m");
}

void				ft_printcolor(va_list arg, int *cursor, t_flags flags)
{
	char	*color;

	color = va_arg(arg, char *);
	ft_color(color);
	flags.zero = 0;
	cursor += 0;
}
