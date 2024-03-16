/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:15:03 by macarval          #+#    #+#             */
/*   Updated: 2024/03/15 22:58:41 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	game;

	inicialize(&game);
	if (argc != 2 || argv[1][0] == '\0')
	{
		ft_putendl_fd("Enter a valid file", 2);
		exit_err(NULL, &game, 1, ERR_ARG);
	}
	else
	{
		get_data(argv, &game);
		init_player(&game);
		draw(&game);
		exec_window(&game);
	}
	return (0);
}

void	inicialize(t_data *game)
{
	game->file_name = NULL;
	game->info.north.file = NULL;
	game->info.south.file = NULL;
	game->info.west.file = NULL;
	game->info.east.file = NULL;
	game->info.floor.r = -1;
	game->info.floor.g = -1;
	game->info.floor.b = -1;
	game->info.ceiling.r = -1;
	game->info.ceiling.g = -1;
	game->info.ceiling.b = -1;
	game->map.map = NULL;
	game->info.north.tex.img = NULL;
	game->info.south.tex.img = NULL;
	game->info.east.tex.img = NULL;
	game->info.west.tex.img = NULL;
	game->exit_code = 0;
	init_window(game);
}
