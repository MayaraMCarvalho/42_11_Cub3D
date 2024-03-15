/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:50:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/03/15 19:52:29 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	defining_walls(t_data *game, t_newRay *new, t_raycast *ray)
{
	new->cast_angle = game->player.ang - ray->ang;
	ray->distance = ray->distance * cos(new->cast_angle);
	new->vertical_line = (WIN_H * WIN_W / 900) / ray->distance;
	new->line_off = WIN_H / 2 - new->vertical_line / 2;
	new->line_y = -1;
	new->ray_horizontal_size = WIN_W / MAX_RAYS;
	set_pixel_texture(ray);
}

static void	find_direction(t_data *game, t_raycast *ray)
{
	if (ray->hor[2] < ray->ver[2])
	{
		ray->distance = ray->hor[2] / SIZE;
		ray->tex = game->info.south;
		if (ray->ang < M_PI)
			ray->tex = game->info.north;
	}
	else
	{
		ray->distance = ray->ver[2] / SIZE;
		ray->tex = game->info.west;
		if (ray->ang > M_PI / 2 && ray->ang < 3 * PI / 2)
			ray->tex = game->info.east;
	}
}

void	get_walls(t_data *game, t_raycast *ray)
{
	t_point		init;
	t_point		dest;
	t_newRay	new;

	find_direction(game, ray);
	defining_walls(game, &new, ray);
	init.x = ray->rays * new.ray_horizontal_size;
	dest.x = ray->rays * new.ray_horizontal_size + new.ray_horizontal_size;
	dest.x--;
	while (++new.line_y < new.vertical_line)
	{
		init.y = new.line_y + new.line_off;
		dest.y = new.line_y + new.line_off;
		ray->pixel[1] = new.line_y * ray->tex.height / new.vertical_line;
		draw_walls(game, init, dest, pixel_color(&ray->tex, ray->pixel));
	}
}
