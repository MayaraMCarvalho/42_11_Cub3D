/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:02:58 by macarval          #+#    #+#             */
/*   Updated: 2024/02/20 15:48:56 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	background_3d(t_img *img, int color, char local)
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

int	convert_color(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

void	get_walls(t_data *game)
{
	int		x;
	int		fd1;//
	float	max;
	float	tam;

	x = WIN_W;
	fd1 = open("dados.txt", O_RDONLY);//
	char	*line = get_next_line(fd1);//
	max = (float) WIN_H;
	if (max < WIN_W)
		max = WIN_W;
	while (line && --x > -1)//
	{//
		tam = ((1.2 * max) - 20) * (max - 0.1) / (atof(line) - 0.1) / 100;
		draw_walls(&game->img, tam, x, 0x111e99);
		free(line);//
		line = get_next_line(fd1);//
	}//
	draw_walls(&game->img, tam, x, 0x111e99);
	free(line);//
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

// int	get_texture(t_data *game, int x, int y)
// {
// 	int	color;

// 	color = 0x12b0ab;
// 	if (y > 0 && game->info.data.map[y - 1][x] == 0) // Norte
// 		color = 0xf00ee4;
// 	else if (x < game->info.data.map_width - 1 && game->info.data.map[y][x + 1] == 0) // Leste
// 		color = 0x111e99;
// 	else if (x > 0 && game->info.data.map[y][x - 1] == 0) // Oeste
// 		color = 0x3eba38;
// 	else if (y < game->info.data.map_height - 1 && game->info.data.map[y + 1][x] == 0) // Sull
// 		color = 0xfcba03;
// 	return (color);
// }

