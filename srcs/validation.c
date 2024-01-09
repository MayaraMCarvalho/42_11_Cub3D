/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:00:14 by macarval          #+#    #+#             */
/*   Updated: 2024/01/09 18:40:03 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validations(char *argv[], t_data *game)
{
	validate_extension(argv[1]);
	validate_open(argv[1], game);
	process_file(game);
	validate_map(game);
}

void	validate_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (strcmp_mod(extension, ".cub"))
	{
		printf("%s: Extension not supported\n", file);
		printf(ERR_ARG);
		exit (4);
	}
}

void	validate_open(char *file, t_data *game)
{
	char	*map;

	map = ft_strjoin("maps/", file);
	game->file = open(map, O_RDONLY);
	free (map);
	if (game->file == -1)
	{
		perror(file);
		printf(ERR_ARG);
		exit (5);
	}
}
