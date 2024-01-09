/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:12:16 by macarval          #+#    #+#             */
/*   Updated: 2024/01/09 15:08:39 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keysym, t_data	*game)
{
	if (keysym == XK_Escape)
		close_window(game);
	// move_frac(keysym, data, 0.1); // move pixel
	return (0);
}

// int	handle_mouse(int button, int x, int y, t_data	*game)
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
// 			zoom_frac(0.5, data);
// 		else
// 			zoom_frac(2, data);
// 		move_zoom(x, y, data);
// 		create_img(game);
// 	}
// 	return (0);
// }

// void	move_frac(int keysym, t_data *data, double dist)
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

// void	zoom_frac(double zoom, t_data	*game)
// {
// 	double	r_center;
// 	double	i_center;

// 	r_center = game->frac.min_r - game->frac.max_r;
// 	i_center = game->frac.max_i - game->frac.min_i;
// 	game->frac.min_r = game->frac.max_r + zoom * r_center;
// 	game->frac.max_r = game->frac.max_r + (r_center - zoom * r_center) / 2;
// 	game->frac.max_i = game->frac.min_i + zoom * (i_center);
// 	game->frac.min_i = game->frac.min_i + (i_center - zoom * i_center) / 2;
// }

// void	move_zoom(int x, int y, t_data	*game)
// {
// 	x -= WIN_W / 2;
// 	y -= WIN_H / 2;
// 	if (x < 0)
// 		move_frac(XK_Right, data, 1 - (double)x / WIN_W);
// 	else if (x > 0)
// 		move_frac(XK_Left, data, (double)x / WIN_W + 0.1);
// 	if (y < 0)
// 		move_frac(XK_Down, data, -(double)y / WIN_H);
// 	else if (y > 0)
// 		move_frac(XK_Up, data, 1 + (double)y / WIN_H);
// }
