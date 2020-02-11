/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:54:10 by abiri             #+#    #+#             */
/*   Updated: 2020/02/11 07:34:52 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flag_processing.h"
#include "virtual_machine.h"

int			ft_verify_player_name(char *filename)
{
	int fd;

	if (!filename)
		return (ft_raise_exception(ERROR_wrong_argument,
			", filename is not specified"));
	else if (!ft_check_file_extension(filename, FILE_EXTENSION))
		return (ft_raise_exception(ERROR_file_extension, filename));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_raise_exception(ERROR_file_open, filename));
	if (read(fd, &fd, 0) < 0)
	{
		close(fd);
		return (ft_raise_exception(ERROR_file_read, filename));
	}
	close(fd);
	return (1);
}

int			ft_player_add_order(void *env, int flag_index, char **params)
{
	t_vm_player	*player;
	t_vm_env	*vm_env;
	int			player_index;

	vm_env = env;
	if (vm_env->init.players.size >= MAX_PLAYERS)
		return (ft_raise_exception(ERROR_player_count, NULL));
	if (!params[0] || !params[1])
		return (ft_raise_exception(ERROR_wrong_argument,
		", try : -n [player_number] [player_file]"));
	else if (!ft_parse_int(params[0], &player_index))
		return (ft_raise_exception(ERROR_wrong_argument,
		", [player_number] should be an integer"));
	else if (player_index < 0 || player_index > MAX_PLAYERS)
		return (ft_raise_exception(ERROR_wrong_argument,
			", [player_number] should be 0 < p < MAX_PLAYERS"));
	else if (!ft_verify_player_name(params[1]))
		return (0);
	if (!(player = ft_memalloc(sizeof(t_vm_player))))
		return (ft_raise_exception(ERROR_allocation_problem, NULL));
	player->index = player_index;
	player->filename = params[1];
	if (!(vm_env->init.players.push(&(vm_env->init.players), player)))
		return (ft_raise_exception(ERROR_allocation_problem, NULL));
	return (flag_index * 0 + 3);
}

int			ft_add_new_player(t_vm_env *vm_env, char *filename)
{
	t_vm_player	*player;

	if (vm_env->init.players.size >= MAX_PLAYERS)
		return (ft_raise_exception(ERROR_player_count, NULL));
	if (!filename)
		return (ft_raise_exception(ERROR_wrong_argument,
		", filename is not specified"));
	else if (!ft_verify_player_name(filename))
		return (0);
	if (!(player = malloc(sizeof(t_vm_player))))
		return (ft_raise_exception(ERROR_allocation_problem, NULL));
	player->index = PLAYER_INDEX_NONE;
	player->filename = filename;
	if (!(vm_env->init.players.push(&(vm_env->init.players), player)))
		return (ft_raise_exception(ERROR_allocation_problem, NULL));
	return (1);
}

t_list_node	*ft_get_next_player(int index, t_list_head *player_list)
{
	t_list_node	*result;
	t_list_node	*node;
	t_vm_player	*player;

	result = NULL;
	player_list->iterator = player_list->first;
	while ((node = ttslist_iter(player_list)))
	{
		player = node->content;
		if (player->index == PLAYER_INDEX_NONE && !result)
			result = node;
		else if (player->index == (index + 1))
			result = node;
	}
	return (result);
}

int			ft_sort_player_list(t_list_head *player_list)
{
	t_list_node	*next_to_place;
	t_vm_player	*player;
	t_list_head	final_list;
	int			index;
	int			player_count;

	ttslist_init(&final_list);
	player_count = player_list->size;
	index = 0;
	while (index < player_count)
	{
		next_to_place = ft_get_next_player(index, player_list);
		if (!next_to_place)
			return (ft_raise_exception(ERROR_player_duplicate_index, NULL));
		player = next_to_place->content;
		player->index = index + 1;
		final_list.push(&final_list, player);
		ttslist_splice(player_list, next_to_place);
		index++;
	}
	if (player_list->size != 0)
		return (ft_raise_exception(ERROR_player_duplicate_index, NULL));
	*player_list = final_list;
	return (1);
}
