/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_processing.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 15:43:02 by abiri             #+#    #+#             */
/*   Updated: 2019/12/30 16:11:08 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_PROCESSING_H
# define FLAG_PROCESSING_H
# define FLAG_COUNT 1

enum	e_commandline_flags
{
	flag_player_number,
	flag_dump,
	flag_visualiser
};

typedef int	t_flag_processor(void *env, int flag_index, char *param);

typedef struct	s_flag_description
{
	char				*flag_name;
	t_flag_processor	*handler;
	int					flag_index;
}				t_flag_description;

/*
**	FLAG CHECKING INTERFACE FUNCTIONS
*/

int	ft_check_args(t_vm_env *vm_env, int argc, char **argv);

/*
**	FLAGS CHECKING HELPER FUNCTIONS
*/

int	ft_activate_flag_bit(void *arg, int flag_index, char *param);

extern const t_flag_description	g_flags_data[];
#endif
