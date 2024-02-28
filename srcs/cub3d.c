/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:15:03 by macarval          #+#    #+#             */
/*   Updated: 2024/02/28 10:04:49 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// talvez mandar uma struct para validate_file e assim setar qualquer
// informação necessária do mapa
int	main(int argc, char *argv[])
{
	t_data	game;

	inicialize(&game);
	if (argc != 2 || argv[1][0] == '\0')
	{
		printf("Enter a valid file\n");
		printf(ERR_ARG);
		exit (1);
	}
	else
	{
		validations(argv, &game);
		init_player(&game);
		draw(&game);
		exec_window(&game);
	}
	return (0);
}

void	inicialize(t_data *game)
{
	game->info.north = NULL;
	game->info.south = NULL;
	game->info.west = NULL;
	game->info.east = NULL;
	game->info.floor.r = -1;
	game->info.floor.g = -1;
	game->info.floor.b = -1;
	game->info.ceiling.r = -1;
	game->info.ceiling.g = -1;
	game->info.ceiling.b = -1;
	game->map.map = NULL;
	game->exit_code = 0;
	init_window(game);
}
