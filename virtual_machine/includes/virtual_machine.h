/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:09:43 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 06:00:05 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

# include "ttslist.h"
# include "libft.h"
# include "op.h"
# include "error_management.h"
# include <ncurses.h>
# include <time.h>
# define FILE_EXTENSION ".cor"
# define BORDER_PADDINGY 2
# define BORDER_PADDINGX 4
# define BORDER_MARGINY 2
# define BORDER_MARGINX 4
# define INFO_PADDING 2
# define INFO_WIDTH 40
# define TEXT_SPEED 1
# define RAW_CURSOR_MODE 11

enum	e_commandline_flags
{
	FLAG_player_number = 1,
	FLAG_dump = 2,
	FLAG_visualizer = 4,
	FLAG_simple_visualiser = 8,
	FLAG_live = 16
};

typedef struct s_op	t_op;

typedef struct	s_vm_init
{
	int			flags;
	int			dump_cycle;
	int			visu_frame;
	int			visu_stop;
	int			cycle_skip;
	t_list_head	players;
}				t_vm_init;

typedef struct	s_vm_players
{
	int				index;
	char			*filename;
	char			*name;
	char			*comment;
	int				exec_size;
	unsigned char	*exec_code;
	int				last_live;
}				t_vm_player;

typedef union	u_intat
{
	char		int1;
	short int	int2;
	int			int4;
}				t_intat;

typedef struct	s_vm_argument
{
	t_intat		value;
	char		type;
}				t_vm_argument;

typedef struct	s_vm_operation
{
	int				op_code;
	t_vm_argument	args[MAX_ARGS_NUMBER];
	int				op_size;
	t_op			*op_data;
	int				error;
}				t_vm_operation;

typedef struct	s_vm_process
{
	int					id;
	int					registers[REG_NUMBER];
	u_int8_t			carry:1;
	long				last_live_cycle;
	long				remaining_cycles;
	int					is_live;
	int					current_position;
	int					last_position;
	int					born_cycle;
	t_vm_operation		operation;
	struct s_vm_arena	*arena;
	t_vm_player			*player;
}				t_vm_process;

typedef struct	s_vm_settings
{
	int			last_alive;
	long		cycles_number;
	long		lives_in_cycle;
	long		cycles_to_die;
	long		number_of_checks;
	long		number_of_checks_from_last_change;
	long		last_period_cycles;
}				t_vm_settings;

typedef struct	s_vm_arena
{
	unsigned char	memory[MEM_SIZE];
	char			colors[MEM_SIZE];
	t_list_head		processes;
}				t_vm_arena;

typedef struct	s_vm_env
{
	t_vm_init		init;
	t_vm_settings	settings;
	t_vm_arena		arena;
}				t_vm_env;

typedef int		t_instruction_exec(t_vm_env *env, t_vm_process *process);

struct			s_op
{
	char				*name;
	int					args_number;
	int					args_type[MAX_ARGS_NUMBER];
	char				op_code;
	int					cycle_number;
	char				*description;
	int					octet_codage;
	int					label_size;
	t_instruction_exec	*exec;
};

extern t_op g_op_tab[17];

/*
**	GENERAL PARSING TOOLS
*/

int				ft_match_charset_times(char *string, char *charset, int min,
		int max);
int				ft_parse_int(char *number, int *integer);
unsigned int	ft_switch_endian(unsigned int value);

/*
** LOADING FUNCTIONS
*/

int				ft_player_add_order(void *env, int flag_index, char **params);
int				ft_add_new_player(t_vm_env	*vm_env, char *filename);
int				ft_sort_player_list(t_list_head *player_list);
int				ft_parse_player(t_vm_player *player);
int				ft_load_players_on_arena(t_vm_env *vm_env);
void			ft_init_game(t_vm_env *env);
int				ft_load_players(t_vm_env *vm_env);
int				ft_init_vm_settings(t_vm_env *vm_env);

/*
**  VISUALIZATION FUNCTIONS
*/

void			ft_init_visualiser(t_vm_env *env);
void			ft_visualiser_update_value(t_vm_env *env,
	int offset, int color, int size);
void			ft_visualiser_draw(t_vm_env *env);
void			ft_visualiser_highlight_process(t_vm_env *env,
	t_vm_process *process);
void			ft_visualiser_unhighlight_process(t_vm_env *env,
	t_vm_process *process);
void			ft_visualiser_draw_memory(t_vm_env *env);
void			ft_visualiser_draw_info(t_vm_env *env);
void			ft_visualiser_handle_keys(t_vm_env *env);
void			ft_visualiser_draw_info_border(void);
void			ft_visualiser_draw_winners(t_vm_env *env, t_vm_player *player);

/*
**  EXECUTION FUNCTIONS
*/

int				ft_add_process(t_vm_env *env, int address, t_vm_player *player);
int				ft_main_vm_loop(t_vm_env *env);
int				ft_execute_instruction(t_vm_env *env, t_vm_process *process,
		t_vm_arena *arena);
int				ft_op_wait(t_vm_env *env, t_vm_process *process, int newborn);

/*
**  OPERATION FUNCTIONS
*/

int				ft_exec_add(t_vm_env *env, t_vm_process *process);
int				ft_exec_aff(t_vm_env *env, t_vm_process *process);
int				ft_exec_and(t_vm_env *env, t_vm_process *process);
int				ft_exec_fork(t_vm_env *env, t_vm_process *process);
int				ft_exec_ld(t_vm_env *env, t_vm_process *process);
int				ft_exec_ldi(t_vm_env *env, t_vm_process *process);
int				ft_exec_lfork(t_vm_env *env, t_vm_process *process);
int				ft_exec_live(t_vm_env *env, t_vm_process *process);
int				ft_exec_lld(t_vm_env *env, t_vm_process *process);
int				ft_exec_lldi(t_vm_env *env, t_vm_process *process);
int				ft_exec_or(t_vm_env *env, t_vm_process *process);
int				ft_exec_st(t_vm_env *env, t_vm_process *process);
int				ft_exec_sti(t_vm_env *env, t_vm_process *process);
int				ft_exec_sub(t_vm_env *env, t_vm_process *process);
int				ft_exec_xor(t_vm_env *env, t_vm_process *process);
int				ft_exec_zjmp(t_vm_env *env, t_vm_process *process);

/*
** HELPER FUNCTIONS
*/

int				ft_valid_opcode(int opcode);
int				ft_modulus(int value, int modulus);
int				ft_limit_address(int value);
int				ft_set_memory_dump(void *arg, int flag_index, char **params);
int				ft_dump_memory(t_vm_env *env);

/*
**  MEMORY ACCESS FUNCTIONS
*/

int				ft_int_endian(int i);
short			ft_short_endian(short i);
int				ft_get_memory(t_vm_process *process, t_vm_argument *argument,
		int *status);
int				ft_set_memory(t_vm_process *process, t_vm_argument *argument,
		t_intat value);
t_intat			ft_read_memory_address(t_vm_arena *arena, int address,
		int size);
void			ft_write_memory_address(t_vm_arena *arena, int address,
		int size, int value);
int				ft_parse_operation(t_vm_process *process, t_vm_arena *arena);
int				ft_get_arguments_types(t_vm_process *process,
	t_vm_arena *arena);
int				ft_get_argument_size(t_vm_argument *arg, t_op *op_data);
char			*ft_check_file_extension(char *filename, char *extension);
void			ft_init_game(t_vm_env *env);
int				ft_check_arguments_errors(t_vm_argument *argument);
int				ft_parse_operation_arguments(t_vm_process *process,
		t_vm_arena *arena);

#endif
