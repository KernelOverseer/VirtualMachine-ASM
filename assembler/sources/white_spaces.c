/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   white_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:28:26 by sou3ada           #+#    #+#             */
/*   Updated: 2020/01/30 07:37:32 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		skip_wsp(char *line)
{
	int	sp;

	sp = 0;
	while (line && ft_ischarin(WHITESPACES, *(line + sp)))
		sp += 1;
	return (sp);
}

int		ignore_wsp(char *line)
{
	int		sp;
	int		len;

	sp = 0;
	len = ft_strlen(line);
	while (len >= 0 && ft_ischarin(WHITESPACES, *(line + len - 1)))
	{
		sp += 1;
		len -= 1;
	}
	return (sp);
}

int		skip_not_wsp(char *line)
{
	int	not_sp;

	not_sp = 0;
	while (line && *(line + not_sp) &&
			!ft_ischarin(WHITESPACES, *(line + not_sp)))
		not_sp += 1;
	return (not_sp);
}
