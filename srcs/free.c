/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:58:38 by macarval          #+#    #+#             */
/*   Updated: 2024/01/09 18:36:38 by macarval         ###   ########.fr       */
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
	if (game->info.north)
		free(game->info.north);
	if (game->info.south)
		free(game->info.south);
	if (game->info.west)
		free(game->info.west);
	if (game->info.east)
		free(game->info.east);
	if (game->info.map)
		free(game->info.map);
}

void	exit_err(char *line, t_data *game, int exit_code)
{
	printf(ERR_SET);
	free_game(game);
	free(line);
	exit (exit_code);
}
