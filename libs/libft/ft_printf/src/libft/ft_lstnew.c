/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebou-nya <ebou-nya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 22:48:06 by ebou-nya          #+#    #+#             */
/*   Updated: 2018/10/20 23:53:39 by ebou-nya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;
	void	*copy;

	node = (t_list*)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	if (content == NULL)
	{
		node->content_size = 0;
		node->content = NULL;
	}
	else
	{
		copy = malloc(content_size);
		if (copy == NULL)
			return (NULL);
		node->content_size = content_size;
		node->content = ft_memcpy(copy, content, content_size);
	}
	node->next = NULL;
	return (node);
}
