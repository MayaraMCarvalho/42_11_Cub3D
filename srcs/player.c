/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:12:56 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/27 09:59:40 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *game)
{
	int		x;
	int		y;
	char	c;
	t_player	*player;

	player = &(game)->player;
	y = -1;
	while (++y < game->map.map_height)
	{
		x = -1;
		while (++x < game->map.map_width)
		{
			if (ft_isalpha(game->map.map[y][x]))
			{
				c = game->map.map[y][x];
				player->x = (x + 0.5) * SIZE;
				player->y = (y + 0.5) * SIZE;
				player->map[0] = x;
				player->map[1] = y;
			}
		}
	}
	if (c == 'N')
		player->ang = M_PI / 2;
	else if (c == 'S')
		player->ang = 3 * M_PI / 2;
	else if (c == 'W')
		player->ang = M_PI;
	else if (c == 'E')
		player->ang = 0;
}
