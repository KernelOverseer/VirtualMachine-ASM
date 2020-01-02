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

#include <mach/task_info.h>
# include "ttslist.h"
# include "libft.h"
# include "op.h"
# include "error_management.h"
# define FILE_EXTENSION ".cor"

typedef struct	s_vm_init
{
	int			flags;
	t_list_head	players;
}				t_vm_init;

typedef struct	s_vm_players_list
{
	int			    index;
	char		    *filename;
	char            *name;
	char            *comment;
	int             exec_size;
	unsigned char   *exec_code;
}				t_vm_player;

typedef struct  s_vm_process
{
    int         id;
    int         registers[REG_NUMBER];
    u_int8_t    carry:1;
    long        last_live_cycle;
    long        remaining_cycles;
    int         current_position;
    int         next_pos_offset;
    //THE ADDRESS OF THE CODE THE PROCESS IS SITTING ON
}               t_vm_process;

typedef struct  s_vm_settings
{
    t_vm_player *last_alive;
    long        cycles_number;
    long        lives_in_cycle;
    long        cycles_to_die;
    long        number_of_checks;
}               t_vm_settings;

typedef struct  s_vm_arena
{
    unsigned char   *memory;
    t_list_head     processes;
}               t_vm_arena;

typedef struct	s_vm_env
{
	t_vm_init	    init;
	t_vm_settings   settings;
	t_vm_arena      arena;
}				t_vm_env;

# include "flag_processing.h"

/*
**	GENERAL PARSING TOOLS
*/

int	ft_match_charset_times(char *string, char *charset, int min, int max);
int	ft_parse_int(char *number, int *integer);
unsigned int ft_switch_endian(unsigned int value);

/*
** LOADING FUNCTIONS
*/

int	ft_player_add_order(void *env, int flag_index, char **params);
int	ft_add_new_player(t_vm_env	*vm_env, char *filename);
int ft_sort_player_list(t_list_head *player_list);
int ft_parse_player(t_vm_player *player);

#endif
