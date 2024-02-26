/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:12:16 by macarval          #+#    #+#             */
/*   Updated: 2024/02/26 19:05:56 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// int	handle_mouse(int button, int x, int y, t_game	*game)
// {
// 	if (button == LEFT_CLICK)
// 		change_color(game);
// 	if (button == RIGHT_CLICK && game->type == JULIA)
// 	{
// 		if (game->j_type == '4')
// 			game->j_type = '1';
// 		else
// 			game->j_type++;
// 	}
// 	if (button == SCROLL_UP || button == SCROLL_DOWN)
// 	{
// 		mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
// 		if (button == SCROLL_UP)
// 			zoom_frac(0.5, game);
// 		else
// 			zoom_frac(2, game);
// 		move_zoom(x, y, game);
// 		create_img(game);
// 	}
// 	return (0);
// }

// void	move_frac(int keysym, t_game *game, double dist)
// {
// 	double	r_center;
// 	double	i_center;

// 	r_center = game->frac.max_r - game->frac.min_r;
// 	i_center = game->frac.max_i - game->frac.min_i;
// 	if (keysym == XK_Left)
// 	{
// 		game->frac.min_r += r_center * dist;
// 		game->frac.max_r += r_center * dist;
// 	}
// 	else if (keysym == XK_Right)
// 	{
// 		game->frac.min_r -= r_center * dist;
// 		game->frac.max_r -= r_center * dist;
// 	}
// 	else if (keysym == XK_Up)
// 	{
// 		game->frac.min_i += i_center * dist;
// 		game->frac.max_i += i_center * dist;
// 	}
// 	else if (keysym == XK_Down)
// 	{
// 		game->frac.min_i -= i_center * dist;
// 		game->frac.max_i -= i_center * dist;
// 	}
// }

void	player_move(t_data *game, float next_x, float next_y)
{
	t_player	*player = &(game)->player;

	if(game->map.map[player->map[1]][(int)(next_x)>>5] != '1')
	{
		player->x = next_x;
		player->map[0] = (int)(next_x)>>5;
	}
	if (game->map.map[(int)(next_y)>>5][player->map[0]] != '1')
	{
		player->y = next_y;
		player->map[1] = (int)(next_y)>>5;
	}
}

int	key_press(int key, t_data *game)
{
	
	// printf("x: %f\n", game->player.x);
	// printf("y: %f\n", game->player.y);
	// printf("y: %f\n", game->player.ang);
	// printf("map_x: %d\n", game->player.map[0]);
	// printf("map_x: %d\n", game->player.map[1]);
	
	t_player	*player = &(game)->player;
	float		cos_a = cos(player->ang) * SPEED;
	float		sin_a = -sin(player->ang) * SPEED;
	
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

	draw(game);
	return (0);
}