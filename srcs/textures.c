/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:53:37 by macarval          #+#    #+#             */
/*   Updated: 2024/03/16 00:04:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_data_textures(t_data *game, t_tex *tex)
{
	tex->tex.img = mlx_xpm_file_to_image(game->mlx, tex->file,
			&tex->width, &tex->height);
	if (!tex->tex.img)
		exit_err(NULL, game, 21, ERR_XPM);
	tex->tex.addr = mlx_get_data_addr(tex->tex.img, &tex->tex.bpp,
			&tex->tex.line_len, &tex->tex.endian);
}

int	pixel_color(t_tex *tex, int *pixel)
{
	int		index;
	t_color	color;

	if (pixel[0] > tex->width)
		pixel[0] %= tex->width;
	if (pixel[1] > tex->height)
		pixel[1] %= tex->height;
	index = (pixel[1] * tex->tex.line_len) + (pixel[0] * (tex->tex.bpp / 8));
	if (index < 0)
		index = 0;
	color.r = tex->tex.addr[index + 2];
	color.g = tex->tex.addr[index + 1];
	color.b = tex->tex.addr[index];
	return (convert_color(color));
}

void	set_pixel_texture(t_raycast *ray)
{
	int	precision;

	if (ray->ver[2] < ray->hor[2])
	{
		precision = (int)((ray->ver[1] / SIZE) * 100) % 100;
		ray->pixel[0] = ray->tex.width * precision / 100;
		if (ray->ang < PI / 2 || ray->ang > 3 * PI / 2)
			ray->pixel[0] = ray->tex.width - ray->pixel[0] - 1;
	}
	else
	{
		precision = (int)((ray->hor[0] / SIZE) * 100) % 100;
		ray->pixel[0] = ray->tex.width * precision / 100;
		if (ray->ang > PI)
			ray->pixel[0] = ray->tex.width - ray->pixel[0] - 1;
	}
}
