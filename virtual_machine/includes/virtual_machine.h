/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:59:55 by abiri             #+#    #+#             */
/*   Updated: 2020/01/25 21:51:35 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE
# define VIRTUAL_MACHINE

#include <mach/task_info.h>
# include "ttslist.h"
# include "libft.h"
# include "op.h"
# include "visualizer.h"
# include "error_management.h"
# define FILE_EXTENSION ".cor"

typedef struct s_op t_op;

typedef struct	s_vm_init
{
	int			flags;
	int			dump_cycle;
	t_list_head	players;
}				t_vm_init;

typedef struct	s_vm_players
{
	int			    index;
	char		    *filename;
	char            *name;
	char            *comment;
	int             exec_size;
	unsigned char   *exec_code;
}				t_vm_player;

typedef union	u_intat
{
	char		int1;
	short int	int2;
	int			int4;
}		t_intat;

typedef struct	s_vm_argument
{
	t_intat		value;
	char		type;
}		t_vm_argument;

typedef struct	s_vm_operation
{
	int		op_code;
	t_vm_argument	args[MAX_ARGS_NUMBER];
	int		op_size;
	t_op    *op_data;
}		t_vm_operation;


typedef struct  s_vm_process
{
    int				    id;
    int				    registers[REG_NUMBER];
    u_int8_t		    carry:1;
    long			    last_live_cycle;
    long			    remaining_cycles;
    int				    current_position;
    int                 last_position;
    int                 born_cycle;
	t_vm_operation	    operation;
    struct  s_vm_arena  *arena;
    t_vm_player         *player;
}               t_vm_process;

typedef struct  s_vm_settings
{
    int         last_alive;
    long        cycles_number;
    long        lives_in_cycle;
    long        cycles_to_die;
    long        number_of_checks;
    long        number_of_checks_from_last_change;
    long        last_period_cycles;
}               t_vm_settings;

typedef struct  s_vm_arena
{
    unsigned char   memory[MEM_SIZE];
    t_list_head     processes;
}               t_vm_arena;

typedef struct	s_vm_env
{
	t_vm_init	    init;
	t_vm_settings   settings;
	t_vm_arena      arena;
}				t_vm_env;

typedef int t_instruction_exec(t_vm_env *env, t_vm_process *process);

struct                  s_op
{
    char			    *name;
    int				    args_number;
    int				    args_type[MAX_ARGS_NUMBER];
    char			    op_code;
    int				    cycle_number;
    char			    *description;
    int				    octet_codage;
    int				    label_size;
    t_instruction_exec  *exec;
};

extern t_op g_op_tab[17];

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
int ft_load_players_on_arena(t_vm_env *vm_env);

/*
**  VISUALIZATION FUNCTIONS
*/

int ft_visualizer_init(t_vm_env *vm_env);

/*
**  EXECUTION FUNCTIONS
*/

int ft_add_process(t_vm_env *env, int address, t_vm_player *player);
int ft_main_vm_loop(t_vm_env *env);
int ft_execute_instruction(t_vm_env *env, t_vm_process *process,
        t_vm_arena *arena);
int ft_op_wait(t_vm_process *process, t_vm_arena *arena);

/*
**  OPERATION FUNCTIONS
*/

int	ft_exec_add(t_vm_env *env, t_vm_process *process);
int	ft_exec_aff(t_vm_env *env, t_vm_process *process);
int	ft_exec_and(t_vm_env *env, t_vm_process *process);
int	ft_exec_fork(t_vm_env *env, t_vm_process *process);
int	ft_exec_ld(t_vm_env *env, t_vm_process *process);
int	ft_exec_ldi(t_vm_env *env, t_vm_process *process);
int	ft_exec_lfork(t_vm_env *env, t_vm_process *process);
int	ft_exec_live(t_vm_env *env, t_vm_process *process);
int	ft_exec_lld(t_vm_env *env, t_vm_process *process);
int	ft_exec_lldi(t_vm_env *env, t_vm_process *process);
int	ft_exec_or(t_vm_env *env, t_vm_process *process);
int	ft_exec_st(t_vm_env *env, t_vm_process *process);
int	ft_exec_sti(t_vm_env *env, t_vm_process *process);
int	ft_exec_sub(t_vm_env *env, t_vm_process *process);
int	ft_exec_xor(t_vm_env *env, t_vm_process *process);
int	ft_exec_zjmp(t_vm_env *env, t_vm_process *process);

/*
** HELPER FUNCTIONS
*/

int ft_valid_opcode(int opcode);
int	ft_modulus(int value, int modulus);
int	ft_limit_address(int value);
int	ft_set_memory_dump(void *arg, int flag_index, char **params);
int	ft_dump_memory(t_vm_env *env);

/*
**  MEMORY ACCESS FUNCTIONS
*/

int     ft_int_endian(int i);
short   ft_short_endian(short i);
int     ft_get_memory(t_vm_process *process, t_vm_argument *argument,
        int *status);
int     ft_set_memory(t_vm_process *process, t_vm_argument *argument,
        t_intat value);
t_intat ft_read_memory_address(t_vm_arena *arena, int address, int size);
void    ft_write_memory_address(t_vm_arena *arena, int address, int size,
                                int value);

#endif
