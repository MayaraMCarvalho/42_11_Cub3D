/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:50:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/03/13 20:09:20 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_color(t_tex *tex, int *pixel)
{
	int		index;
	int		red;
	int		green;
	int		blue;

	if (pixel[0] > tex->width)
		pixel[0] %= tex->width;
	if (pixel[1] > tex->height)
		pixel[1] %= tex->height;
	index = (pixel[1] * tex->tex.line_len) + (pixel[0] * (tex->tex.bpp / 8));
	if (index < 0)
		index = 0;
	red = tex->tex.addr[index + 2];
	green = tex->tex.addr[index + 1];
	blue = tex->tex.addr[index];
	return ((red << 16) + (green << 8) + blue);
}

void	set_texture(t_raycast *ray)
{
	int	precision;

	if (ray->ver[2] < ray->hor[2])
	{
		precision = (int)((ray->ver[1] / SIZE) * 100) % 100;
		ray->pixel[0]= ray->tex.width * precision / 100;
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

void	draw_rectangle(t_data *game, t_point start, t_point end, int color)
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

void	set_3d_cast(t_data *game, t_newRay *new, t_raycast *ray)
{
	new->cast_angle = game->player.ang - ray->ang;
	if (new->cast_angle < 0)
		new->cast_angle += 2 * M_PI;
	if (new->cast_angle > 2 * M_PI)
		new->cast_angle -= 2 * M_PI;
	ray->distance = ray->distance * cos(new->cast_angle);
	new->vertical_line = (WIN_H * WIN_W / 950) / ray->distance;
	new->line_off = WIN_H / 2 - new->vertical_line / 2;
	new->line_y = -1;
	new->ray_horizontal_size = WIN_W / MAX_RAYS;
	set_texture(ray);
}

void	define_texture(t_data *game, t_raycast *ray)
{
	if (ray->hor[2] < ray->ver[2])
	{
		ray->distance = ray->hor[2] / SIZE;
		if (ray->ang < M_PI)
			ray->tex = game->info.north;
		else
			ray->tex = game->info.south;
	}
	else
	{
		ray->distance = ray->ver[2] / SIZE;
		if (ray->ang > M_PI / 2 && ray->ang < 3 * PI / 2)
			ray->tex = game->info.east;
		else
			ray->tex = game->info.west;
	}
}

void	get_walls(t_data *game, t_raycast *ray)
{
	t_point		init;
	t_point		dest;
	t_newRay	new;

	define_texture(game, ray);
	set_3d_cast(game, &new, ray);
	init.x = ray->rays * new.ray_horizontal_size;
	dest.x = ray->rays * new.ray_horizontal_size + new.ray_horizontal_size;
	dest.x--;
	while (++new.line_y < new.vertical_line)
	{
		init.y = new.line_y + new.line_off;
		dest.y = new.line_y + new.line_off;
		ray->pixel[1] = new.line_y * ray->tex.height / new.vertical_line;
		draw_rectangle(game, init, dest, get_texture_color(&ray->tex, ray->pixel));
	}
}
