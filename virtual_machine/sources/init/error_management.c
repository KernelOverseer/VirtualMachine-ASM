/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:38:35 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 16:11:28 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

char	*g_error_strings[] =
{
	"Unknown flag",
	"Wrong command line arguments",
	"Cannot allocate enough memory",
	"Cannot open file",
	"Cannot read file",
	"Wrong file extension",
	"Number of players exceeded MAX_PLAYERS",
	"Players cannot be order in the given way",
	"No players given to the virtual machine",
	"Magic header format wrong for file :",
	"Error in player name for file :",
	"Wrong size of player executable :",
	"Player executable size is bigger than the limit in file :",
	"Error in player comment for file :",
	"Incomplete code or wrong size of executable code in file :",
	"Trailing bytes in player executable code in file :"
};

int		ft_raise_exception(int error_code, char *custom)
{
	char	*error_string;

	error_string = g_error_strings[error_code];
	ft_putstr_fd("\e[1m\e[91mERROR :\e[0m ", 2);
	ft_putstr_fd(error_string, 2);
	if (custom)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(custom, 2);
	}
	ft_putchar_fd('\n', 2);
	return (ERROR);
}
