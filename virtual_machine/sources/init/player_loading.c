/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_loading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:52:22 by abiri             #+#    #+#             */
/*   Updated: 2020/02/06 15:53:52 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void	ft_destroy_player(t_vm_player *player)
{
	if (player)
	{
		free(player->exec_code);
		free(player->comment);
		free(player->name);
		player->exec_code = NULL;
		player->comment = NULL;
		player->name = NULL;
	}
}

static int	ft_load_player_exec_code(int fd, t_vm_player *player)
{
	int end_of_file_check;

	player->exec_code = ft_memalloc(sizeof(unsigned char) * player->exec_size);
	if (read(fd, player->exec_code, player->exec_size) != player->exec_size)
	{
		ft_destroy_player(player);
		return (ft_raise_exception(ERROR_player_incomplete_code,
			player->filename));
	}
	if (read(fd, &end_of_file_check, 1) != 0)
	{
		ft_destroy_player(player);
		return (ft_raise_exception(ERROR_player_trailing_bytes,
			player->filename));
	}
	return (SUCCESS);
}

static int	ft_load_player(int fd, t_vm_player *player)
{
	unsigned char	name_buffer[PROG_NAME_LENGTH + 4];
	unsigned char	comment_buffer[COMMENT_LENGTH + 4];
	unsigned int	verification;

	if (read(fd, name_buffer, PROG_NAME_LENGTH + 4) != PROG_NAME_LENGTH + 4)
		return (ft_raise_exception(ERROR_player_name, player->filename));
	if (*((unsigned int *)(name_buffer + PROG_NAME_LENGTH)) != 0)
		return (ft_raise_exception(ERROR_player_name, player->filename));
	if (read(fd, &verification, 4) != 4 ||
			ft_switch_endian(verification) > CHAMP_MAX_SIZE)
		return (ft_raise_exception(ERROR_player_bigger_size, player->filename));
	player->exec_size = ft_switch_endian(verification);
	if (read(fd, comment_buffer, COMMENT_LENGTH + 4) != COMMENT_LENGTH + 4)
		return (ft_raise_exception(ERROR_player_comment, player->filename));
	if (*((unsigned int *)(comment_buffer + COMMENT_LENGTH)) != 0)
		return (ft_raise_exception(ERROR_player_comment, player->filename));
	player->name = ft_strdup((char *)name_buffer);
	player->comment = ft_strdup((char *)comment_buffer);
	return (ft_load_player_exec_code(fd, player));
}

static int	ft_check_magic_header(int fd)
{
	unsigned int	magic_header;

	if (read(fd, &magic_header, 4) != 4)
		return (ERROR);
	magic_header = ft_switch_endian(magic_header);
	if (magic_header != COREWAR_EXEC_MAGIC)
		return (ERROR);
	return (SUCCESS);
}

int			ft_parse_player(t_vm_player *player)
{
	int			fd;
	int			status;

	status = SUCCESS;
	if ((fd = open(player->filename, O_RDONLY)) < 0)
		return (ft_raise_exception(ERROR_file_open, player->filename));
	if (!ft_check_magic_header(fd))
		status = ft_raise_exception(ERROR_magic_header, player->filename);
	if (status && !ft_load_player(fd, player))
		status = ERROR;
	close(fd);
	return (status);
}
