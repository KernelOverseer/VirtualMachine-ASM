/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 04:27:24 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/01 05:33:40 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		ft_isint(char *str)
{
	int	i;

	if (str[0] == '-')
		i = 0;
	else
		i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int		type_size(int type, int id)
{
	if (type == T_REG)
		return (1);
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_DIR)
		return (DIR_SIZE - (g_op_tab[id].label_size ? 2 : 0));
	return (0);
}

/*
**  LABELS are automatically defined as T_IND
*/

int		str_type_arg(char *arg)
{
	if (arg && *arg == DIRECT_CHAR)
		return (T_DIR);
	if (arg && *arg == REGISTER_CHAR)
		return (T_REG);
	if (arg && ft_isint(arg))
		return (T_IND);
	if (arg && *arg == LABEL_CHAR)
		return (T_IND);
	return (0);
}

int		line_to_manage(char *line)
{
	if ((line && (line[0] != COMMENT_CHAR && line[0] != COMMENT_CHAR_2))
			&& !ft_strequ(line, ""))
		return (1);
	return (0);
}

void	replace_newline(char *line)
{
	if (*(line + ft_strlen(line) - 1) == '\n')
		*(line + ft_strlen(line) - 1) = '\0';
}
