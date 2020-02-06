/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:05:29 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 17:05:31 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_ERROR_MANAGEMENT_H
# define COREWAR_ERROR_MANAGEMENT_H

enum	e_error_management
{
	ERROR_wrong_flag,
	ERROR_wrong_argument,
	ERROR_allocation_problem,
	ERROR_file_open,
	ERROR_file_read,
	ERROR_file_extension,
	ERROR_player_count,
	ERROR_player_duplicate_index,
	ERROR_no_players,
	ERROR_magic_header,
	ERROR_player_name,
	ERROR_player_wrong_size,
	ERROR_player_bigger_size,
	ERROR_player_comment,
	ERROR_player_incomplete_code,
	ERROR_player_trailing_bytes
};

extern char *g_error_strings[];

int ft_raise_exception(int error_code, char *custom);
#endif
