/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_from_header.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 04:04:15 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/03 03:21:46 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	write_exec_magic(int filedesc)
{
	int	magic;

	magic = COREWAR_EXEC_MAGIC;
	ft_write_int(filedesc, magic);
}

void	write_command_name(int filedesc, t_asm *data)
{
	char	name_bytes[PROG_NAME_LENGTH];

	ft_bzero(name_bytes, PROG_NAME_LENGTH);
	ft_strcpy(name_bytes, data->cmd_name);
	ft_write_bytes(filedesc, (unsigned char*)name_bytes, PROG_NAME_LENGTH);
	ft_write_int(filedesc, 0);
}

void	write_command_comment(int filedesc, t_asm *data)
{
	char	comment_bytes[COMMENT_LENGTH];

	ft_bzero(comment_bytes, COMMENT_LENGTH);
	ft_strcpy(comment_bytes, data->cmd_comment);
	ft_write_bytes(filedesc, (unsigned char*)comment_bytes, COMMENT_LENGTH);
	ft_write_int(filedesc, 0);
}

void	write_champ_exec_code(int fildesc, t_asm *data)
{
	ft_write_int(fildesc, data->size_champ);
}

int		write_file(t_asm *data)
{
	int		filedesc;

	if ((filedesc = create_file(data)) < 0)
		return (0);
	write_exec_magic(filedesc);
	write_command_name(filedesc, data);
	write_champ_exec_code(filedesc, data);
	write_command_comment(filedesc, data);
	write_instructions(filedesc, data->instructions);
	close(filedesc);
	return (1);
}
