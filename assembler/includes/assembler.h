/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:34:30 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/03 04:30:44 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H
# include "op.h"
# include "libft.h"
# include <errno.h>
# include <stdio.h>

extern char	*g_error_strings[];

typedef struct	s_arguments
{
	char	*name;
	int		type;
}				t_arg;

typedef struct	s_instructions
{
	int						line;
	char					*label;
	int						id;
	char					*name;
	int						size;
	t_arg					*args[3];
	struct s_instructions	*tail;
	struct s_instructions	*next;
}				t_inst;

typedef struct	s_label
{
	int		id;
	t_inst	*addr;
}				t_label;

typedef struct	s_asm
{
	char	*file_name;
	char	*cmd_name;
	char	*cmd_comment;
	int		size_champ;
	t_label	*labels;
	t_inst	*instructions;
}				t_asm;

int				parse_args(char *filename, t_asm *data);
int				read_file(int filedesc, t_asm *data);

void			allocate_asm(t_asm **data);
void			initialize_asm(t_asm **data, char *arg);
void			initialize_instruction(t_inst **instructions);
void			allocate_label(t_label **label);

int				skip_not_wsp(char *line);
int				ignore_wsp(char *line);
int				skip_wsp(char *line);

void			ft_find_comment(char *line);
int				command_isname(char *line);
int				command_iscomment(char *line);
int				store_name_command(t_asm *data, char *line,
				int filedesc, char *command_buffer);
int				store_comment_command(t_asm *data, char *line,
				int filedesc, char *command_buffer);

int				get_instructions(char *line, t_asm *data, int *code);

int				manage_label(char *line, t_inst *inst);
int				label_simple_line(int *num, int cursor,
				t_asm *data, t_inst *new);
void			store_label(t_label **labels, t_inst *list);

int				manage_arguments(char *line, t_inst *new);
int				check_valid_args(t_inst *inst);
int				str_type_arg(char *arg);
int				type_size(int type, int id);
int				update_size_instruction(t_inst *inst);
int				line_to_manage(char *line);
void			replace_newline(char *line);

int				replace_label_value(t_inst *inst, t_asm *data, int index);
int				get_value(t_asm *data, int current_line, int position);

int				create_file(t_asm *data);
int				write_file(t_asm *data);
void			write_instructions(int filedesc, t_inst *inst);

void			ft_write_short(int filedesc, short value);
void			ft_write_int(int filedesc, int value);
void			ft_write_bytes(int filedesc, unsigned char *bytes, size_t size);

int				free_s_asm(t_asm **data, char **line, int permission);
int				free_s_asm_node(t_asm **data);
void			free_s_instructions(t_inst **inst);
int				force_quit(char *line, t_asm **data, t_inst **inst);
int				ft_raise_exception(int error_code, char *custom);

int				ft_isint(char *str);
int				store_command(int fd, char *line, char *buffer,
				size_t buffsize);
int				get_multi_line(int fd, int inquote, char *buffer,
				size_t buffsize);
int				multi_line_content(int inquote, int filedesc,
				int buffsize, char *buffer);
int				get_inquote(char *line, int *inquote, char *buffer,
				size_t buffsize);
char			*initialize_variables(char *buffer, int *inquote,
				int *index, size_t *buffer_index);
int				check_buffer_size(int buffsize, int buffer_index);

int				get_line(int const fd, char **line);

#endif
