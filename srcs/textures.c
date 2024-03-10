/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:53:37 by macarval          #+#    #+#             */
/*   Updated: 2024/03/10 17:26:49 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_data_textures(t_data *game, t_tex *tex)
{
	tex->tex.img = mlx_xpm_file_to_image(game->mlx, tex->file,
			&tex->width, &tex->height);
	if (!tex->tex.img)
	{
		printf("%s", ERR_XPM);
		game->exit_code = 21;
		close_window(game);
	}
	tex->tex.addr = mlx_get_data_addr(tex->tex.img, &tex->tex.bpp,
			&tex->tex.line_len, &tex->tex.endian);
}

int	convert_color(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

int	get_pixel_color(t_data *game, int x, int y, int guide)
{
	int		index;
	int		red;
	int		green;
	int		blue;
	t_tex	tex;

	tex = define_texture(game, guide);
	if (x > tex.width)
		x %= tex.width;
	if (y > tex.height)
		y %= tex.height;
	index = ((y * tex.tex.line_len) + (x * (tex.tex.bpp / 8)));
	if (index < 0)
		index = 0;
	red = tex.tex.addr[index + 2];
	green = tex.tex.addr[index + 1];
	blue = tex.tex.addr[index];
	return ((red << 16) + (green << 8) + blue);
}

t_tex	define_texture(t_data *game, int guide)
{
	t_tex	tex;

	tex = game->info.south;
	if (guide == EAST)
		tex = game->info.east;
	else if (guide == NORTH)
		tex = game->info.north;
	else if (guide == WEST)
		tex = game->info.west;
	return (tex);
}
