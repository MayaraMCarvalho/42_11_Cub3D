/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:03:34 by macarval          #+#    #+#             */
/*   Updated: 2024/02/27 10:50:11 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_data *game, float next_x, float next_y)
{
	t_player	*player;

	player = &(game)->player;
	if (game->map.map[player->map[1]][(int)(next_x) >> 5] != '1')
	{
		player->x = next_x;
		player->map[0] = (int)(next_x) >> 5;
	}
	if (game->map.map[(int)(next_y) >> 5][player->map[0]] != '1')
	{
		player->y = next_y;
		player->map[1] = (int)(next_y) >> 5;
	}
}

int	key_press(int key, t_data *game)
{
	verify_key(key, game);
	draw(game);
	return (0);
}

void	verify_key(int key, t_data *game)
{
	t_player	*player;
	float		cos_a;
	float		sin_a;

	player = &(game)->player;
	cos_a = cos(player->ang) * SPEED;
	sin_a = -sin(player->ang) * SPEED;
	if (key == ESC_KEY)
		close_window(game);
	if (key == W_KEY)
		player_move(game, player->x + cos_a, player->y + sin_a);
	if (key == S_KEY)
		player_move(game, player->x - cos_a, player->y - sin_a);
	if (key == A_KEY)
		player_move(game, player->x - SPEED, player->y);
	if (key == D_KEY)
		player_move(game, player->x + SPEED, player->y);
	if (key == LEFT_KEY)
		player->ang += 0.1;
	if (key == RIGHT_KEY)
		player->ang -= 0.1;
	if (player->ang < 0)
		player->ang += 2 * M_PI;
	if (player->ang > (2 * M_PI -0.00001))
		player->ang -= 2 * M_PI;
}
