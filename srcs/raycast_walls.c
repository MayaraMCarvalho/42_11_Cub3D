/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:50:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/03/08 20:22:41 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_walls(t_data *game, t_raycast *ray)
{
	float	max;
	float	tam;
	float	distance;

	distance = ray->ver[2];
	if (distance > ray->hor[2])
		distance = ray->hor[2];
	max = (float) WIN_H;
	if (max < WIN_W)
		max = WIN_W;
	distance *= cos(game->player.ang - ray->ang);
	tam = ((1.2 * max) - 20) * (max - 0.1) / (distance - 0.1) / 100;
	if (tam - floor(tam) > 0.4)
		tam += 1.0;
	draw_walls(game, tam, ray->rays, get_guide(ray));
}

int	get_guide(t_raycast *ray)
{
	int	guide;

	if (ray->hor[2] < ray->ver[2])
	{
		guide = SOUTH;
		if (ray->ang > 0 && ray->ang < 2 * PI)
			guide = NORTH;
	}
	else
	{
		guide = WEST;
		if (ray->ang > 0 && ray->ang < 2 * PI)
			guide = EAST;
	}
	return (guide);
}
