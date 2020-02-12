/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 04:39:02 by aelouarg          #+#    #+#             */
/*   Updated: 2020/02/12 01:50:59 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "libft.h"

static	unsigned int	ft_linelen(char *tab, int *newline)
{
	unsigned int	i;

	i = 0;
	while (tab[i] != '\0')
	{
		if (tab[i] == '\n')
		{
			*newline = 2;
			return (++i);
		}
		i++;
	}
	return (i);
}

static	char			*ft_line(char *tab, int *newline)
{
	if (ft_strchr(tab, '\n'))
	{
		ft_strcpy(tab, ft_strchr(tab, '\n') + 1);
		return (tab);
	}
	if (ft_linelen(tab, newline) > 0)
	{
		ft_strcpy(tab, ft_strchr(tab, '\0'));
		return (tab);
	}
	return (NULL);
}

int						get_line(int const fd, char **line)
{
	char			*tmp;
	int				newline;
	char			buff[BUFF_SIZE + 1];
	static char		*tab[MAX_FD];
	int				ret;

	newline = 1;
	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(tab[fd]) && (tab[fd] = ft_strnew(0)) == NULL)
		return (-1);
	while (!(ft_strchr(tab[fd], '\n')) && (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = tab[fd];
		tab[fd] = ft_strnjoin(tmp, buff, ret);
		free(tmp);
	}
	*line = ft_strsub(tab[fd], 0, ft_linelen(tab[fd], &newline));
	if (ft_line(tab[fd], &newline) == NULL)
	{
		tab[fd] ? ft_memdel((void**)&tab[fd]) : 0;
		return (0);
	}
	return (newline);
}
