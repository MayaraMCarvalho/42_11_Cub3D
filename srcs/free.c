/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:58:38 by macarval          #+#    #+#             */
/*   Updated: 2024/01/18 19:42:29 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char ***split)
{
	int		i;
	char	**temp;

	i = -1;
	temp = *split;
	while (temp[++i])
		free(temp[i]);
	free(*split);
}

void	free_game(t_data *game)
{
	if (game->file_name)
		free(game->file_name);
	if (game->info.north)
		free(game->info.north);
	if (game->info.south)
		free(game->info.south);
	if (game->info.west)
		free(game->info.west);
	if (game->info.east)
		free(game->info.east);
	if (game->info.data.map)
		free_map(game);
	if (game->mlx)
		free(game->mlx);
}

void	free_map(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->info.data.map_height)
		free(game->info.data.map[i]);
	free(game->info.data.map);
}

void	exit_err(char *line, t_data *game, int exit_code, char *err)
{
	printf("%s", err);
	free_game(game);
	if (line)
		free(line);
	exit (exit_code);
}
