/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:20:52 by abiri             #+#    #+#             */
/*   Updated: 2020/01/01 16:09:34 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

char    *ft_check_file_extension(char *filename, char *extension)
{
    char *ext;

    if (!filename)
        return (NULL);
    ext = ft_strrchr(filename, '.');
    if (ext == filename || !ext)
        return (NULL);
    if (ft_strequ(ext, extension))
        return (ext);
    return (NULL);
}

int     ft_verify_player_name(char *filename)
{
    int fd;

    if (!filename)
        return (ft_raise_exception(ERROR_wrong_argument, ", filename is not specified"));
    if (!ft_check_file_extension(filename, FILE_EXTENSION))
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

int	ft_player_add_order(void *env, int flag_index, char **params)
{
	t_vm_env			*vm_env;
	t_vm_player	*player;
	int					player_index;

	(void)flag_index;
	vm_env = env;
    if (vm_env->init.players.size >= MAX_PLAYERS)
        return (ft_raise_exception(ERROR_player_count, NULL));
	if (!params[0] || !params[1])
		return (ft_raise_exception(ERROR_wrong_argument, ", try : -n [player_number] [player_file]"));
	if (!ft_parse_int(params[0], &player_index))
		return (ft_raise_exception(ERROR_wrong_argument, ", [player_number] should be an integer"));
	if (player_index < 0 || player_index > MAX_PLAYERS)
	    return (ft_raise_exception(ERROR_wrong_argument, ", [player_number] should be 0 < p < MAX_PLAYERS"));
    if (!ft_verify_player_name(params[1]))
        return (0);
	if (!(player = ft_memalloc(sizeof(t_vm_player))))
		return (ft_raise_exception(ERROR_allocation_problem, NULL));
	player->index = player_index;
	player->filename = params[1];
	if (!(vm_env->init.players.push(&(vm_env->init.players), player)))
		return (ft_raise_exception(ERROR_allocation_problem, NULL));
	return (3);
}

int	ft_add_new_player(t_vm_env	*vm_env, char *filename)
{
	t_vm_player	*player;

    if (vm_env->init.players.size >= MAX_PLAYERS)
        return (ft_raise_exception(ERROR_player_count, NULL));
	if (!filename)
		return (ft_raise_exception(ERROR_wrong_argument, ", filename is not specified"));
	if (!ft_verify_player_name(filename))
	    return (0);
	if (!(player = ft_memalloc(sizeof(t_vm_player))))
		return (ft_raise_exception(ERROR_allocation_problem, NULL));
	player->index = PLAYER_INDEX_NONE;
	player->filename = filename;
	if (!(vm_env->init.players.push(&(vm_env->init.players), player)))
		return (ft_raise_exception(ERROR_allocation_problem, NULL));
	return (1);
}

int ft_sort_player_list(t_list_head *player_list)
{
    t_list_node         *node;
    t_list_node         *next_to_place;
    t_vm_player         *player;
    t_list_head         final_list;
    int                 index;
    int                 player_count;

    ttslist_init(&final_list);
    player_count = player_list->size;
    index = 0;
    while (index < player_count)
    {
        player_list->iterator = player_list->first;
        next_to_place = NULL;
        while ((node = ttslist_iter(player_list)))
        {
            player = node->content;
            if (player->index == PLAYER_INDEX_NONE && !next_to_place)
                next_to_place = node;
            if (player->index == (index + 1))
                next_to_place = node;
        }
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