/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:03:34 by macarval          #+#    #+#             */
/*   Updated: 2024/02/28 10:53:01 by macarval         ###   ########.fr       */
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
	if (key != ESC_KEY && verify_key(key, game))
		draw(game);
	return (0);
}

int	key_press_esc(int key, t_data *game)
{
	if (key == ESC_KEY)
		close_window(game);
	return (0);
}

int	verify_key(int key, t_data *game)
{
	t_player	*player;
	float		cos_a;
	float		sin_a;
	int			control;

	control = 0;
	player = &(game)->player;
	cos_a = cos(player->ang) * SPEED;
	sin_a = -sin(player->ang) * SPEED;
	if (key == W_KEY && ++control)
		player_move(game, player->x + cos_a, player->y + sin_a);
	if (key == S_KEY && ++control)
		player_move(game, player->x - cos_a, player->y - sin_a);
	if (key == A_KEY && ++control)
		player_move(game, player->x - SPEED, player->y);
	if (key == D_KEY && ++control)
		player_move(game, player->x + SPEED, player->y);
	control += update_ang(key, player);
	return (control);
}

int	update_ang(int key, t_player *player)
{
	int	control;

	control = 0;
	if (key == LEFT_KEY && ++control)
		player->ang += 0.1;
	if (key == RIGHT_KEY && ++control)
		player->ang -= 0.1;
	if (player->ang < 0 && ++control)
		player->ang += 2 * M_PI;
	if (player->ang > (2 * M_PI -0.00001) && ++control)
		player->ang -= 2 * M_PI;
	return (control);
}
