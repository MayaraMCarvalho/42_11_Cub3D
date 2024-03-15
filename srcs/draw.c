/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:00:39 by joapedr2          #+#    #+#             */
/*   Updated: 2024/03/15 19:16:25 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x > WIN_W || y > WIN_H || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_background(t_img *img, int color, char local)
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

void	draw_walls(t_data *game, t_point start, t_point end, int color)
{
	int	x;
	int	y;

	y = start.y - 1;
	while (++y <= end.y)
	{
		x = start.x - 1;
		while (++x <= end.x)
			put_pixel_img(&game->img, x, y, color);
	}
}

void	draw(t_data *game)
{
	draw_background(&game->img, convert_color(game->info.ceiling), 'C');
	draw_background(&game->img, convert_color(game->info.floor), 'F');
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
