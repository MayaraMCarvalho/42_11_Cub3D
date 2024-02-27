/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:00:39 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/27 09:22:42 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert_color(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

static void	draw_background(t_img *img, int color, char local)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIN_W)
	{
		y = -1;
		if (local == 'F')
			y += WIN_H / 2;
		while (++y <= WIN_H)
			put_pixel_img(img, x, y, color);
	}
}

void	draw_walls(t_img *img, int tam, int x, int color)
{
	int	y;

	y = (WIN_H - tam) / 2;
	while (++x < WIN_W)
	{
		while (++y <= (WIN_H + tam) / 2)
			put_pixel_img(img, x, y, color);
	}
}

void	draw(t_data *game)
{
	draw_background(&game->img, convert_color(game->info.ceiling), 'C');
	draw_background(&game->img, convert_color(game->info.floor), 'F');
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
