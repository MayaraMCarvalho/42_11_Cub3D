/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:50:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/03/10 16:53:02 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_new_ray
{
	int		color;
	float	distance;
	int		ray_horizontal_size;
	int		vertical_line;
	float	cast_angle;
	int		line_off;
	int		line_y;
}	t_newRay;

void	draw_rectangle(t_data *data, t_point start, t_point end, int color)
{
	int	x;
	int	y;

	y = start.y;
	while (y <= end.y)
	{
		x = start.x;
		while (x <= end.x)
		{
			put_pixel_img(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	set_3d_cast(t_data *game, t_newRay *new, t_raycast *ray)
{
	new->cast_angle = game->player.ang - ray->ang;
	if (new->cast_angle < 0)
		new->cast_angle += 2 * M_PI;
	if (new->cast_angle > 2 * M_PI)
		new->cast_angle -= 2 * M_PI;
	new->distance = new->distance * cos(new->cast_angle);
	new->vertical_line = 980 / new->distance;
	new->line_off = WIN_H / 2 - new->vertical_line / 2;
	new->line_y = -1;
	new->ray_horizontal_size = WIN_W / MAX_RAYS;
}

void get_walls(t_data *game, t_raycast *ray)
{
	t_point init;
	t_point	dest;
	t_newRay new;

	new.color = 0x800000;
	if (ray->hor[2] <= ray->ver[2])
		new.distance = ray->hor[2] / SIZE;
	else
	{	
		new.distance = ray->ver[2] / SIZE;
		new.color = 0xFA0008;	
	}
	
	set_3d_cast(game, &new, ray);
	init.x = ray->rays * new.ray_horizontal_size;
	dest.x = ray->rays * new.ray_horizontal_size + new.ray_horizontal_size;
	dest.x--;
	while (++new.line_y < new.vertical_line)
	{
		init.y = new.line_y + new.line_off;
		dest.y = new.line_y + new.line_off;
		draw_rectangle (game, init, dest, new.color);
	}
}
