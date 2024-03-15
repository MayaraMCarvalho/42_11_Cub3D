/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:00:14 by macarval          #+#    #+#             */
/*   Updated: 2024/03/12 11:55:47 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_data(char *argv[], t_data *game)
{
	int		final_set;

	validate_extension(argv[1], game);
	validate_open(argv[1], game);
	final_set = process_settings(game);
	process_map(game, final_set);
	get_map(game);
	validate_map(game);
	get_data_textures(game, &game->info.north);
	get_data_textures(game, &game->info.south);
	get_data_textures(game, &game->info.west);
	get_data_textures(game, &game->info.east);
}

void	validate_extension(char *file, t_data *game)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (strcmp_mod(extension, ".cub"))
	{
		printf("%s: Extension not supported\n", file);
		exit_err(NULL, game, 22, ERR_ARG);
	}
}

void	validate_open(char *file, t_data *game)
{
	game->file_name = ft_strjoin("maps/", file);
	game->fd = open(game->file_name, O_RDONLY);
	if (game->fd == -1)
		exit_err(NULL, game, 23, ERR_ARG);
}

void	validate_map(t_data *game)
{
	int		error;
	int		j;
	int		i;

	j = -1;
	error = 0;
	while (++j < game->map.height && game->map.map[j])
	{
		i = -1;
		while (++i < game->map.width && game->map.map[j][i])
		{
			error += validate_errors(game, j, i);
			if (error > 1)
				exit_err(NULL, game, 18, ERR_MAP_MORE);
		}
	}
	if (!error)
		exit_err(NULL, game, 20, ERR_MAP_MISS);
}

int	validate_errors(t_data *game, int j, int i)
{
	int		error;

	error = 0;
	if (((j == 0 || !game->map.map[j + 1])
			&& !ft_strchr("1\t\n ", game->map.map[j][i]))
		|| (game->map.map[j][i] == '0'
		&& !check_neighbors(game, j, i, "01NSEW")))
		exit_err(NULL, game, 16, ERR_MAP_OPEN);
	if (!ft_strchr("01NSEW\n ", game->map.map[j][i]))
		exit_err(NULL, game, 17, ERR_MAP_DISALLOW);
	if (ft_strchr("NSEW", game->map.map[j][i]))
	{
		error = 1;
		if (!check_neighbors(game, j, i, "01"))
			exit_err(NULL, game, 19, ERR_MAP_LOCAL);
	}
	return (error);
}
