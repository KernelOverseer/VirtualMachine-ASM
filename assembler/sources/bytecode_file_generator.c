/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_file_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:19:51 by aelouarg          #+#    #+#             */
/*   Updated: 2020/02/03 03:20:11 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	create_file(t_asm *data)
{
	int		filedesc;
	char	*name;
	char	*path;

	name = ft_strsub(data->file_name, 0, ft_strlen(data->file_name) - 2);
	path = ft_strjoin(name, ".cor");
	ft_memdel((void**)&name);
	if ((filedesc = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777)) < 0)
	{
		ft_memdel((void**)&path);
		return (-1);
	}
	ft_memdel((void**)&path);
	return (filedesc);
}
