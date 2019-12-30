/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:28:49 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/20 22:46:52 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(const char *str, char c)
{
	int		i;
	int		count;
	int		new_word;

	new_word = 1;
	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != c) && new_word == 1)
		{
			count++;
			new_word = 0;
		}
		else if (str[i] == c)
			new_word = 1;
		i++;
	}
	return (count);
}
