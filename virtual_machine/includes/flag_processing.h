/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_processing.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 15:43:02 by abiri             #+#    #+#             */
/*   Updated: 2020/02/09 04:57:00 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_PROCESSING_H
# define FLAG_PROCESSING_H
# define FLAG_COUNT 4
# define PLAYER_INDEX_NONE -1

enum	e_commandline_flags
{
	FLAG_player_number = 1,
	FLAG_dump = 2,
	FLAG_visualizer = 4,
	FLAG_simple_visualiser = 8
};

typedef int				t_flag_processor(void *env, int flag_index,
	char **params);

typedef struct			s_flag_description
{
	char				*flag_name;
	t_flag_processor	*handler;
	int					flag_index;
}						t_flag_description;

/*
**	FLAG CHECKING INTERFACE FUNCTIONS
*/

int						ft_check_args(t_vm_env *vm_env, int argc,
	char **argv);

/*
**	FLAGS CHECKING HELPER FUNCTIONS
*/

int						ft_activate_flag_bit(void *arg, int flag_index,
	char **param);

extern const t_flag_description	g_flags_data[];
#endif
