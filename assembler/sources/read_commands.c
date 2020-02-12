/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:40:35 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 07:40:09 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_find_comment(char *line)
{
	int index;
	int	inquote;

	index = 0;
	inquote = 0;
	while (line[index])
	{
		if (line[index] == '"')
			inquote ^= 1;
		if (!inquote &&
			(line[index] == COMMENT_CHAR || line[index] == COMMENT_CHAR_2))
		{
			*(line + index) = '\0';
			return ;
		}
		index++;
	}
	return ;
}

int		command_isname(char *line)
{
	char	*command;

	command = NULL;
	if ((command = ft_strstr(line, NAME_CMD_STRING)) && !(line - command))
		return (1);
	return (0);
}

int		command_iscomment(char *line)
{
	char	*command;

	command = NULL;
	if ((command = ft_strstr(line, COMMENT_CMD_STRING)) && !(line - command))
		return (1);
	return (0);
}
