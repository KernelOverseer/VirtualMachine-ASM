/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 21:17:39 by mherrat           #+#    #+#             */
/*   Updated: 2018/10/19 23:32:30 by mherrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_wordlenth(const char *str, char c)
{
	int counter;

	counter = 0;
	while (str[counter] != c && str[counter] != '\0')
		counter++;
	return (counter);
}

static	int		ft_words_count(const char *str, char c)
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

static	char	*wordtotable(const char **s, char c, size_t *i)
{
	char *string;

	if ((string = (char *)malloc(sizeof(char)
					* (ft_wordlenth(*s, c) + 1))))
	{
		while (**s != c && **s != '\0')
		{
			string[*i] = **s;
			(*s)++;
			(*i)++;
		}
		string[*i] = '\0';
		return (string);
	}
	else
	{
		return (NULL);
	}
}

char			**ft_strsplit(char const *s, char c)
{
	char	**table;
	size_t	j;
	size_t	i;

	if (s == NULL)
		return (NULL);
	j = 0;
	if (!(table = (char **)malloc(sizeof(char *) * (ft_words_count(s, c) + 1))))
		return (NULL);
	while (*s != '\0')
	{
		i = 0;
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		if (*s != c && *s != '\0')
		{
			table[j] = wordtotable(&s, c, &i);
		}
		j++;
	}
	table[j] = 0;
	return (table);
}
