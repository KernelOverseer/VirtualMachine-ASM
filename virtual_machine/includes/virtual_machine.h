/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:59:55 by abiri             #+#    #+#             */
/*   Updated: 2019/12/30 19:33:08 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE
# define VIRTUAL_MACHINE
# include "ttslist.h"
# include "libft.h"

typedef struct	s_vm_init
{
	int			flags;
	int			next_player_index;
	t_list_head	players;
}				t_vm_init;

typedef struct	s_vm_players_list
{
	int			index;
	char		*filename;
}				t_vm_players_list;

typedef struct	s_vm_env
{
	t_vm_init	init;
}				t_vm_env;

# include "flag_processing.h"

/*
**	GENERAL PARSING TOOLS
*/

int	ft_match_charset_times(char *string, char *charset, int min, int max);
int	ft_parse_int(char *number, int *integer);

/*
** LOADING FUNCTIONS
*/

int	ft_player_add_order(void *env, int flag_index, char **params);
int	ft_add_new_player(t_vm_env	*vm_env, char *filename);

#endif
