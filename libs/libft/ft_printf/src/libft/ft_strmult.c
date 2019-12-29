/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 08:28:37 by aelouarg          #+#    #+#             */
/*   Updated: 2019/05/10 05:31:30 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		c_val(char c)
{
	if (c > 64 && c < 91)
		return (c + 10 - 'A');
	return (c - '0');
}

static char		c_char(int val)
{
	if (val > 10)
		return (val - 10 + 'A');
	return (val + '0');
}

static char		*ft_put_into_s(int *result, int n1, int n2)
{
	int			i;
	char		*s;

	i = n1 + n2 - 1;
	while (i >= 0 && result[i] == 0)
		i--;
	if (i == -1)
	{
		free(result);
		return (ft_strcnew(1, '0'));
	}
	s = ft_strnew(0);
	while (i >= 0)
		s = ft_str_pushback(s, c_char(result[i--]));
	free(result);
	return (s);
}

static int		init_m(t_mult *m, char *num1, char *num2)
{
	m->n1 = ft_strlen(num1);
	m->n2 = ft_strlen(num2);
	if (!m->n1 || !m->n2)
		return (-1);
	m->result = (int*)ft_memalloc(sizeof(int) * (m->n1 + m->n2));
	m->i_n1 = 0;
	m->i_n2 = 0;
	m->i = m->n1;
	return (0);
}

char			*ft_strmult(char *num1, char *num2, int base)
{
	t_mult		m;

	if (init_m(&m, num1, num2) == -1)
		return (ft_strcnew(1, '0'));
	while (m.i-- > 0)
	{
		m.carry = 0;
		m.i_n2 = 0;
		m.j = m.n2;
		while (m.j-- > 0)
		{
			m.sum = c_val(num1[m.i]) * c_val(num2[m.j])
				+ m.result[m.i_n1 + m.i_n2] + m.carry;
			m.carry = m.sum / base;
			m.result[m.i_n1 + m.i_n2] = m.sum % base;
			m.i_n2++;
		}
		(m.carry > 0) ? m.result[m.i_n1 + m.i_n2] += m.carry : 0;
		m.i_n1++;
	}
	m.s = ft_put_into_s(m.result, m.n1, m.n2);
	return (m.s);
}
