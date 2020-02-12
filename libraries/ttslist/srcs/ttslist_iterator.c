/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttslist_iterator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 03:00:49 by abiri             #+#    #+#             */
/*   Updated: 2020/02/12 01:31:58 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ttslist.h"

void		*ttslist_iter_content(t_list_head *head)
{
	void				*result;

	if (!head->iterator)
		return (NULL);
	result = head->iterator->content;
	head->iterator = head->iterator->next;
	return (result);
}

t_list_node	*ttslist_iter(t_list_head *head)
{
	t_list_node			*result;

	if (!head->iterator)
		return (NULL);
	result = head->iterator;
	head->iterator = head->iterator->next;
	return (result);
}

void		*ttslist_get_id_content(t_list_head *head, int id)
{
	void	*content;

	head->iterator = head->first;
	while ((content = ttslist_iter_content(head)))
	{
		if (!id)
			return (content);
		id--;
	}
	return (NULL);
}
