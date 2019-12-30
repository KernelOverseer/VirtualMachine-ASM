/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 07:23:27 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/25 07:23:29 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static char		*ft_itoaplus(unsigned int number, char *result)
{
	if (number >= 10)
	{
		ft_itoaplus(number / 10, result + 1);
		*result = number % 10 + '0';
	}
	else
		*result = number % 10 + '0';
	return (result);
}

static char		*ft_chnumber(unsigned int number)
{
	char			*dest;
	unsigned int	nbr;
	int				size;

	size = 1;
	nbr = number;
	while (nbr /= 10)
		size++;
	dest = (char *)malloc(sizeof(char) * size);
	while (size)
		dest[size--] = 0;
	return (ft_strrev(ft_itoaplus(number, dest)));
}

static void		ft_cat(char *s1, const char *s2, int **cursor)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = -1;
	result = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[++i])
		result[i] = s1[i];
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	ft_putstr(result);
	*(*cursor) += ft_strlen(result);
}

void			ft_printtime(va_list arg, int *cursor, t_flags flags)
{
	long		duration;

	duration = (long)va_arg(arg, long);
	if (duration == 1)
		ft_cat(ft_chnumber(duration), " second ago.", &cursor);
	else if (duration < 60)
		ft_cat(ft_chnumber(duration), " seconds ago.", &cursor);
	else if (duration / 60 == 1)
		ft_cat(ft_chnumber(duration / 60), " minute ago.", &cursor);
	else if (duration > 60 && duration < 3600)
		ft_cat(ft_chnumber(duration / 60), " minutes ago.", &cursor);
	else if (duration / 3600 == 1)
		ft_cat(ft_chnumber(duration / 3600), " hour ago.", &cursor);
	else if (duration / 3600 != 1 && duration < 86400)
		ft_cat(ft_chnumber(duration / 3600), " hours ago.", &cursor);
	else if (duration / 86400 == 1)
		ft_cat(ft_chnumber(duration / 86400), " day ago.", &cursor);
	else if (duration / 86400 != 1 && duration < 2592000)
		ft_cat(ft_chnumber(duration / 86400), " days ago.", &cursor);
	else if (duration / 2592000 == 1)
		ft_cat(ft_chnumber(duration / 2592000), " month ago.", &cursor);
	else
		ft_cat(ft_chnumber(duration / 2592000), " months ago.", &cursor);
	(void)flags.zero;
}
